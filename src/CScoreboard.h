#include "stdafx.h"

#define SCOREBOARD_MAX_INDEX 32

// In addition to these, the scoreboard also shows defkit/bomb status and health,
// but these are not stored here. Indices 1..32 match engine player indices.
struct scoreboard_entry_s {
    int id;
    int score;
    int frags;
    int deaths;
    int headshots;
    int teamId;
};

extern scoreboard_entry_s g_ScoreboardData[SCOREBOARD_MAX_INDEX + 1];

class CScoreboard {
public:
    CScoreboard();
    static void Draw();
    void setVisible(bool value);

private:
    bool bIsVisible;
};
