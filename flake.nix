checks.${system} = {
  devEnv = pkgs.mkShell {
    packages = devPackages;
  };

  buildBinary = pkgs.stdenv.mkDerivation {
    name = "electric-era-submission";
    src = ./.;
    buildPhase = ''
      mkdir -p $out/bin
      g++ -std=c++17 -O2 main.cpp -o $out/bin/submission
    '';
    installPhase = "true";
  };

  runBinary = pkgs.stdenv.mkDerivation {
    name = "run-electric-era-submission";
    src = ./.;
    nativeBuildInputs = [ pkgs.gcc ];
    buildPhase = ''
      echo "🔧 Building and running submission..."
      g++ -std=c++17 -O2 main.cpp -o submission
      output=$(./submission)

      expected="Hello, Electric Era!"

      if [ "$output" != "$expected" ]; then
        echo "❌ Output mismatch!"
        echo "Expected: $expected"
        echo "Got:      $output"
        exit 1
      fi

      echo "✅ Output matched expected: $output"
    '';
    installPhase = "true";
  };
};
