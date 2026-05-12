## v1.1.0 (2026-05-12)

### Feat

- update `CClassicHealthBar` class with new design and better indicating reloading/planting status
- add bomb and timer icons to topbar
- add possibility to adjust font weight (but haven't added command)
- display skull sprite instead of HP in case of death

### Fix

- HP number aligned to center
- use custom topbar background to solve text z-index issue

### Refactor

- remove unused `CCSPHealthBar`

## v1.0.0 (2026-05-07)

### Feat

- update setting team's flag command to only require alpha2 country code instead of full path
- team_1 is now on the left and is terrorists, team_2 is on the right and is counter-terrorists
- add build & release workflow
- add ci workflow
- update in-game spectator GUI & assets

### Fix

- strip tags stripping the wrong part of nicknames

### Refactor

- update flag images
- bump lodepng version
- update CFont class to use truetype fonts
- format code with clang-format
