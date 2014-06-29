#ifndef MAINTYPES_H
#define MAINTYPES_H

#define COMMON_TYPES_PER_COLOR 3
#define FORBIDDEN_TYPES_PER_COLOR 2
#define TYPES_PER_SET 10
#define NORMAL_ABIL_DIE 0.5
#define CARDS_IN_SET 120
#define CARDS_PER_COLOR 30
#define TYPES_IN_SET 10
#define BASE_CHANCE_FOR_COMMON_TYPE 0.5
#define CHANCE_FOR_DUAL_TYPE 0.2
#define CHANCE_FOR_FIRST_ABILITY 0.8
#define CHANCE_FOR_SECOND_ABILITY 0.5
#define CHANCE_FOR_THIRD_ABILITY 0.3
#define BASE_CHANCE_FOR_FAVORED_ABILITY 0.3
#define CHANCE_TO_TARGET_ALL 0.25


/*Target types*/
#define LOCAL 0
#define COLOR 1
#define CARDTYPE 2
#define ANY 3

typedef enum {opposing,self,rnd_friend,rnd_enemy,type_friend,type_enemy,color_friend,color_enemy,all_friend,all_enemy} target_type;



struct color{
 int id;
 int common[COMMON_TYPES_PER_COLOR];
 int forbidden[FORBIDDEN_TYPES_PER_COLOR];
 int allowed[TYPES_IN_SET-COMMON_TYPES_PER_COLOR-FORBIDDEN_TYPES_PER_COLOR];
 int hated_color;
};

struct card_type{
 char name[20];
 char name_pl[20];
 int id;
 int fave_ability1,fave_ability2;
 int enemy,buddy;
 double hp_die,att_die,crit_die,abil_die;
};


struct ability{
 int ability_type; 
 int chance;
 int target_by,target_detail;
 int multihit;


};


struct card{
 int id;
 char name[40];
 int color;
 char dual;
 int type,type2;
 int hp,att,crit;
 int n_abil;
 struct ability ab[3];
};

struct set
{
 unsigned long seed;
 struct card cardlist[CARDS_IN_SET];
 int type_ids[TYPES_IN_SET];
 struct card_type types[TYPES_IN_SET];
 struct color setcolors[4];
};


#endif