{pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-24.05") {} }:
pkgs.mkShell {
  packages = [
    pkgs.bison
    pkgs.flex
  ];
}