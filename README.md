# HLTV Health bars

A tool for watching HLTV demos and live HLTV servers.
Mostly used by Counter-Strike 1.6 streamers in the 2010s.

## Features

- Set up team names and flags
- Team total score
- Round & bomb timers
- Health bars (including team, nick, HP, current weapon, bomb/defuse kit, reloading status)

## Usage

1. Download the latest release
2. Extract the archive into your counter strike 1.6 folder (replace existing files, it's harmless,
   but you may want to make a backup first)
3. Run the game, make sure it runs in 1280x720 resolution (otherwise may need to tweak configs)
4. Inject the dll in `<your game folder>/hltv_healthbars/hltv_healthbars.dll` to `hl.exe` process using
   [Extreme Injector](https://github.com/master131/extremeinjector) or any other suitable tool
5. Open in-game console and type `exec 720.cfg`
6. Connect to HLTV server with `hltv_connect IP` or play a demo
7. Type `hltv_help` to print available commands
8. Enjoy
9. (optional) Download & install `Roboto Condensed` font
   from [Google Fonts](https://fonts.google.com/specimen/Roboto+Condensed)

## Building from source

1. Clone this repo with `git clone --recursive https://github.com/ValveSoftware/hltv_healthbars.git`
2. Load cmake project and compile

## Contributing

Issues and pull requests are welcome in any form

## References

Most of the code is based on the source code once published on gamedeception.net by some dick jones.
The original code is stored in kallkod branch.

Country flags are provided by awesome https://github.com/hampusborgos/country-flags

Timer icon is a Fontawesome icon

https://wiki.alliedmods.net/Half-Life_1_Game_Events#Health

https://ftgl.sourceforge.net/docs/html/ftgl-tutorial.html

https://web.archive.org/web/20120107075444/http://www.gamedeception.net/threads/22277-Healthbars/page4

https://web.archive.org/web/20120106231641/http://www.gamedeception.net/threads/22277-Healthbars/page3

https://web.archive.org/web/20120106231250/http://www.gamedeception.net/threads/22277-Healthbars/page2
