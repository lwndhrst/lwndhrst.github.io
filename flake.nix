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
      devShell.${system} = pkgs.mkShell {
        buildInputs = with pkgs; [
          bundler
          jekyll
          rubyPackages.jekyll-feed
          rubyPackages.jekyll-redirect-from
          rubyPackages.webrick
        ];
      };
    };
}
