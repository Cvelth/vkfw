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

      devShells.clang =
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
            "-pthread"

            "-I${pkgs.lib.makeIncludePath [pkgs.glibc.dev]}"
            "-I${pkgs.lib.makeIncludePath [llvm.libcxx.dev]}/c++/v1"
            "-I${pkgs.lib.makeIncludePath [pkgs.glfw]}"
            "-I${pkgs.lib.makeIncludePath [pkgs.vulkan-headers]}"

            "-I${inputs.glfw-source}/deps"
          ];

          LDFLAGS = [
            "--stdlib=libc++"
            "-pthread"

            "-L${pkgs.lib.makeLibraryPath [pkgs.vulkan-loader]}"
            "-L${pkgs.lib.makeLibraryPath [llvm.libcxx]}"
            "-L${pkgs.lib.makeLibraryPath [pkgs.glfw]}"
          ];
        };

      devShells.gcc =
        pkgs.mkShell.override {
          stdenv = pkgs.gcc15Stdenv;
        } {
          buildInputs = [
            pkgs.gcc15

            pkgs.cmake
            pkgs.ninja

            pkgs.glfw
            pkgs.vulkan-loader
            pkgs.vulkan-headers
            pkgs.vulkan-validation-layers
            pkgs.vulkan-tools
          ];

          CC = "gcc";
          CXX = "g++";
          LD = "ld";

          CXXFLAGS = [
            "-std=c++23"
            "-fmodules-ts"
            "-pthread"

            "-I${pkgs.lib.makeIncludePath [pkgs.glfw]}"
            "-I${pkgs.lib.makeIncludePath [pkgs.vulkan-headers]}"
            "-I${pkgs.lib.makeIncludePath [pkgs.glibc.dev]}"

            "-I${inputs.glfw-source}/deps"
          ];

          CMAKE_CXX_STANDARD = "23";
          CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP = "1";

          LDFLAGS = [
            "-L${pkgs.lib.makeLibraryPath [pkgs.vulkan-loader]}"
            "-L${pkgs.lib.makeLibraryPath [pkgs.glfw]}"
            "-pthread"
          ];
        };
    });
}
