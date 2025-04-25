{
  description = "Electric Era Challenge C++ Dev Environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };

    devPackages = with pkgs; [
      gcc
      cmake
      gnumake
      gdb
      valgrind
    ];
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = devPackages;

      shellHook = ''
        echo "⚡ Welcome to the Electric Era dev shell"
      '';
    };

    checks.${system}.devEnv = pkgs.mkShell {
      packages = devPackages;
    };

    checks.${system}.buildBinary = pkgs.stdenv.mkDerivation {
      name = "electric-era-submission";
      src = ./.; # current directory
      buildPhase = ''
        mkdir -p $out/bin
        g++ -std=c++17 -O2 main.cpp -o $out/bin/submission
      '';
      installPhase = "true"; # no extra install steps
    };
  };
}
