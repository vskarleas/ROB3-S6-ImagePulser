#!/bin/bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install opencv
brew install cmake
myArray=("evince" "gtk+" "doxygen" "azure-cli" "opencv" "openexr" "libtiff" "libpng" "jpeg" "gnuplot" "adwaita-icon-theme" "sdl2" "SDL2_image" "SDL2_ttf" "libevent" "amtk" "libffi" "aom" "libgedit-amtk" "apr" "libgedit-gtksourceview" "apr-util" "libidn2" "argon2" "libnghttp2" "arm-none-eabi-test" "libpeas" "aspell" "libpng" "atk" "libpsl" "autoconf" "libpthread-stubs" "automake" "librsvg" "bdw-gc" "libsodium" "bison" "libsoup" "brotli" "libssh2" "c-ares" "libtasn1" "ca-certificates" "libtiff" "cairo" "libtool" "cask" "libunistring" "chruby" "libuv" "cocoapods" "libvmaf" "coreutils" "libx11" "cowsay" "libxau" "curl" "libxcb" "duck" "libxdmcp" "emacs" "libxext" "enchant" "libxml2" "fontconfig" "libxrender" "freetds" "libyaml" "freetype" "libzip" "fribidi" "little-cms2" "fswatch" "lz4" "gd" "lzo" "gdbm" "m4" "gdk-pixbuf" "mpdecimal" "gedit" "netpbm" "gettext" "nettle" "giflib" "nghttp2" "git" "node" "glib" "oniguruma" "glib-networking" "opam" "gmp" "openexr" "gnutls" "openjdk" "gobject-introspection" "openldap" "gpatch" "openssl"@"1"."1" "graphite2" "openssl"@"3" "graphviz" "p11"-"kit" "gsettings-desktop-schemas" "pango" "gspell" "pcre" "gtk"+ "pcre2" "gtk"+"3" "pixman" "gtk-mac-integration" "pkg-config" "gtksourceview4" "py3cairo" "gts" "pygobject3" "guile" "python"@"3"."11" "harfbuzz" "python"@"3"."9" "hcloud" "readline" "heroku-node" "redis" "hicolor-icon-theme" "rtmpdump" "highway" "ruby-install" "hugo" "sqlite" "icu4c" "tepl" "imath" "tidy-html5" "iso-codes" "tree-sitter" "jansson" "uchardet" "jasper" "unbound" "jemalloc" "unixodbc" "jpeg" "vala" "jpeg-turbo" "webp" "jpeg-xl" "wimlib" "krb5" "xorgproto" "libavif" "xz" "libepoxy" "zstd" "libev" "putty" "nedit" "arm-none-eabi-gcc")
for str in ${myArray[@]}; do
  echo "Installing $str . . ."
  brew install $str
done