{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";

    glfw-source = {
      url = "github:glfw/glfw/3.4";
      flake = false;
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  } @ inputs:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};

      llvm = pkgs.llvmPackages_20;
    in {
      formatter = pkgs.alejandra;

      devShells.default =
        pkgs.mkShell.override {
          stdenv = llvm.libcxxStdenv;
        } {
          buildInputs = [
            llvm.clang
            llvm.lld
            llvm.clang-tools

            llvm.libcxx

            pkgs.cmake
            pkgs.ninja

            pkgs.glfw
            pkgs.vulkan-loader
            pkgs.vulkan-headers
            pkgs.vulkan-validation-layers
            pkgs.vulkan-tools
          ];

          CC = "clang";
          CXX = "clang++";
          LD = "lld";

          CXXFLAGS = [
            "--stdlib=libc++"
            "-I${llvm.libcxx.dev}/include/c++/v1"
            "-I${inputs.glfw-source}/deps"
            "-I${pkgs.glfw}/include"
            "-I${pkgs.vulkan-headers}/include"
            "-pthread"
          ];

          LDFLAGS = [
            "--stdlib=libc++"
            "-L${llvm.libcxx}/lib"
            "-L${pkgs.glfw}/lib"
            "-pthread"
          ];

          CPATH = "${pkgs.glibc.dev}/include:$CPATH";
          LD_LIBRARY_PATH = "${
            pkgs.lib.makeLibraryPath [pkgs.vulkan-loader]
          }:$LD_LIBRARY_PATH";
        };
    });
}
