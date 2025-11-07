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
          bear
          cmake
          cpr
          curl
          ftxui
          gdb
          meson
          ninja
          nlohmann_json
          openssl
        ];

        shellHook = ''
          echo "🛠️  C++ dev shell with Clang"
          echo "🔧  Compiler: $("${pkgs.clang}/bin/clang" --version | head -n 1)"
          echo "🔧  Compiler: $("${pkgs.gcc}/bin/gcc" --version | head -n 1)"
        '';
      };
      packages.wftcli = pkgs.stdenv.mkDerivation {
        pname = "warframe-trade-cli";
        version = "0.0.1";

        src = ./.;

        nativeBuildInputs = with pkgs; [
          cmake
          gcc
          pkg-config
        ];
        buildInputs = with pkgs; [
          cpr
          curl
          ftxui
          nlohmann_json
        ];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
          "-DCPR_USE_SYSTEM_CURL=ON"
        ];
      };

      packages.wftcli-debug = pkgs.stdenv.mkDerivation {
        pname = "warframe-trade-cli-debug";
        version = "0.0.1";

        src = ./.;

        nativeBuildInputs = with pkgs; [
          cmake
          gcc
          pkg-config
        ];
        buildInputs = with pkgs; [
          cpr
          curl
          ftxui
          nlohmann_json
        ];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Debug"
          "-DCPR_USE_SYSTEM_CURL=ON"
        ];
      };
    });
}
