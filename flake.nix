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

    checks.${system}.default = pkgs.mkShell {
      packages = devPackages;
    };
  };
}
