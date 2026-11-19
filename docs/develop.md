# Develop

Beamdown is C++ and Qt Quick. Build it as in [Get started](start.md), then:

`bin/build` uses a Qt toolchain under `build/qt/` when present, then falls back to `qmake6` on your PATH. It checks for Qt 6.9 or newer before compiling. Set `HYPE_QMAKE=/path/to/qmake6` to select a different toolchain. Internal names, such as the `HYPE_*` variables and the `hype-tests` binary, keep Hype's name.

Run `./bin/test` for the regression suite. After building the tests, the presenter
check can also run with two virtual displays:

```sh
HYPE_GUI_TESTS=1 QT_QPA_PLATFORMTHEME=generic QT_STYLE_OVERRIDE=Fusion \
  QT_QPA_PLATFORM="offscreen:configfile=$PWD/tests/fixtures/presenter-screens.json" \
  ./build/tests/hype-tests presenterViewUsesSeparateScreens
```
