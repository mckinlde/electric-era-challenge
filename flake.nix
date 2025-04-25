{
  description = "Electric Era Challenge C++ Dev Environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: {
    devShells.x86_64-linux.default = let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
    in pkgs.mkShell {
      packages = with pkgs; [
        gcc
        cmake
        gnumake
        gdb
        valgrind
      ];

      shellHook = ''
        echo "⚡ Welcome to the Electric Era dev shell"
      '';
    };

    checks.x86_64-linux.default = let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
    in pkgs.mkShell {
      packages = with pkgs; [
        gcc
        cmake
        gnumake
        gdb
        valgrind
      ];
    };
  };
}

