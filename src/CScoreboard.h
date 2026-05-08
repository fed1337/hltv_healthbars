#include "stdafx.h"


// In addition to these, the scoreboard also shows defkit/bomb status and health,
// but these are not stored here
struct scoreboard_entry_s {
    int id;
    int score;
    int frags;
    int deaths;
    int headshots;
};

extern scoreboard_entry_s g_ScoreboardData[32];


class CScoreboard {
public:
    void Draw();
    void setVisible(bool value);

private:
    bool bIsVisible;
};
