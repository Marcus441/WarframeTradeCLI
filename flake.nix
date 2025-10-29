{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShell = pkgs.mkShell {
        name = "C++ DevShell";

        buildInputs = with pkgs; [
          cmake
          bear
          gdb
          meson
          ninja
          openssl
          nlohmann_json
          cpr
          curl
        ];

        shellHook = ''
          echo "🛠️  C++ dev shell with Clang"
          echo "🔧  Compiler: $("${pkgs.clang}/bin/clang" --version | head -n 1)"
        '';
      };
      packages.wftcli = pkgs.stdenv.mkDerivation {
        pname = "warframe-trade-cli";
        version = "0.0.1";

        src = ./.;

        nativeBuildInputs = with pkgs; [
          gcc
          cmake
          pkg-config
        ];
        buildInputs = with pkgs; [
          cpr
          curl
          nlohmann_json
        ];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
          "-DCPR_USE_SYSTEM_CURL=ON"
        ];

        # buildPhase = ''
        #   cmake -S . -B build $cmakeFlags
        #   cmake --build build --parallel
        # '';
        #
        # installPhase = ''
        #   cmake --install build --prefix $out
        # '';
      };
    });
}
