{
  inputs = {
    nixpkgs = {
      url = "github:nixos/nixpkgs/nixos-unstable";
    };
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

    in {
      devShell.${system} = pkgs.mkShell.override { stdenv = pkgs.llvmPackages.stdenv; } {
        packages = with pkgs; [
          pkg-config

          clang-tools
          cmake
          emscripten
          ninja
          python3

          # for compiling GLFW with Wayland
          # libffi
          # libxkbcommon
          # wayland
          # wayland-scanner
        ];

        shellHook = ''
          export EM_CACHE="$(pwd)/build/emscripten-cache"; # emscripten tries to write to its nix store path without this
        '';
      };
    };
}
