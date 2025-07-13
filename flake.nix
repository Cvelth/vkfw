{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";

    gcc-trunk = {
      url = "github:gcc-mirror/gcc";
      flake = false;
    };

    glfw-source = {
      url = "github:glfw/glfw/3.4";
      flake = false;
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    gcc-trunk,
    ...
  } @ inputs:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};

      llvm = pkgs.llvmPackages_20;

      gcc-trunk-derivation = pkgs.stdenv.mkDerivation {
        name = "gcc-trunk";
        src = gcc-trunk;

        nativeBuildInputs = [
          pkgs.gmp
          pkgs.mpfr
          pkgs.libmpc
          pkgs.isl
          pkgs.flex
        ];

        configureFlags = [
          "--disable-bootstrap"

          "--enable-languages=c,c++,lto"
          "--disable-multilib"

          "--with-gmp=${pkgs.gmp}"
          "--with-mpfr=${pkgs.mpfr}"
          "--with-mpc=${pkgs.libmpc}"
          "--with-isl=${pkgs.isl}"

          "--with-native-system-header-dir=${pkgs.lib.makeIncludePath [pkgs.stdenv.cc.libc.dev]}"
        ];

        LIBRARY_PATH = "${pkgs.lib.makeLibraryPath [pkgs.stdenv.cc.libc]}";

        enableParallelBuilding = true;

        # GCC does not build with `-Werror=format-security`
        hardeningDisable = ["format"];
      };
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

      # This shell relies on a pretty dodgy build of a not-yet-released version
      # of gcc. I do not recommend you use it for anything but basic testing.
      devShells.gcc-trunk =
        pkgs.mkShell.override {
          stdenv = pkgs.stdenvNoCC;
        } {
          buildInputs = [
            gcc-trunk-derivation
            pkgs.binutils

            pkgs.cmake
            pkgs.ninja

            pkgs.glfw
            pkgs.vulkan-loader
            pkgs.vulkan-headers
            pkgs.vulkan-validation-layers
            pkgs.vulkan-tools
          ];

          CC = "${gcc-trunk-derivation}/bin/gcc";
          CXX = "${gcc-trunk-derivation}/bin/g++";
          LD = "ld";

          CXXFLAGS = [
            "-std=c++23"
            "-fmodules-ts"
            "-pthread"
            "-I${pkgs.lib.makeIncludePath [pkgs.glibc.dev]}"
            "-I${pkgs.lib.makeIncludePath [pkgs.glfw]}"
            "-I${pkgs.lib.makeIncludePath [pkgs.vulkan-headers]}"

            "-I${inputs.glfw-source}/deps"
          ];

          CMAKE_CXX_STANDARD = "23";
          CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP = "1";

          LDFLAGS = [
            "-pthread"

            "-L${pkgs.lib.makeLibraryPath [pkgs.vulkan-loader]}"
            "-L${pkgs.lib.makeLibraryPath [pkgs.glfw]}"
          ];

          LIBRARY_PATH = "${pkgs.lib.makeLibraryPath [pkgs.stdenv.cc.libc]}";
        };
    });
}
