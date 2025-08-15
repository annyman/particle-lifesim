# Maintainer: annyman <annyman.81194@protonmail.com>
pkgname=particle-lifesim
pkgver=0.1.4
pkgrel=1
pkgdesc="A particle-based artificial life simulation, implemented with raylib and C++"
arch=('x86_64')
url="https://github.com/annyman/particle-lifesim"
license=('MIT')
makedepends=('meson' 'ninja' 'gcc')
depends=('raylib')
source=("$url/archive/refs/tags/v${pkgver}.tar.gz")
sha256sums=('0845044edf07fba45b0d71c69127630d03ece09e23396beb303a99aa19625ab9')

build() {
    cd "${pkgname}-${pkgver}"
    meson setup build --buildtype debug
    meson compile -C build
}

package() {
    cd "${pkgname}-${pkgver}"
    meson install -C build --destdir="$pkgdir"
    install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}