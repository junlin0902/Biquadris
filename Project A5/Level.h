#ifndef _LEVEL_H_
#define _LEVEL_H_

class Level {
    protected:
    int cur_level;
    bool is_random;

    public:
    int get_curlevel() {return cur_level;}
    void level_up();
    void level_down();
};

class Level0: public Level {

};

class Level1: public Level {
    
};

class Level2: public Level {
    
};

class Level3: public Level {
    
};

class Level4: public Level {
    
};

#endif
