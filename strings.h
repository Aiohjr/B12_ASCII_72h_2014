#ifndef STRINGS_H
#define STRINGS_H

 #define N_TYPES 47
 #define N_FNAMES 52
 #define N_LNAMES 52
 #define N_ABILITIES 11
 
 #define BENEFIT 0
 #define HARM 1
 #define SPECIAL 2
 #define MULTI 1
 #define SINGLE 0
 
 char colors[][6] = {"Cyan","Red","White","Green"};
 char types_single[N_TYPES][20] = {"Adventurer","Alien","American","Anarchist","Angel","Beast","Cannibal","Clone","Clown","Commoner","Courtesan","Cowboy","Cult","Democrat","Demon","Detective","Engineer","Faery","French","German","Gladiator","Hauler","Hitman","Japanese","Journalist","Mafia","Mason","Merchant","Ninja","Noble","Officer","Peasant","Pirate","Policeman","Politician","Psycho","Rebel","Republican","Robot","Royalty","Russian","Slave","Soldier","Spy","Vampire","Witch","Zombie"};
 char types_pl[N_TYPES][20] = {"Adventurers","Aliens","Americans","Anarchists","Angels","Beasts","Cannibals","Clones","Clowns","Commoners","Courtesans","Cowboys","Cultists","Democrats","Demons","Detectives","Engineers","Faerys","French","German","Gladiators","Haulers","Hitmen","Japanese","Journalists","Mafia","Masons","Merchants","Ninjas","Nobles","Officers","Peasants","Pirates","Police","Politicians","Psychos","Rebels","Republicans","Robots","Royalty","Russians","Slaves","Soldiers","Spies","Vampires","Witches","Zombies"};
 char firstnames[][20] = {"Albert","Alina","Boris","Benny","Chris","Capt'n","Dave","Diana","Elbert","Ernst","Fanny","Fedor","Grigory","Goon","Harold","Helen","Irvin","Ichiko","Jane","Jim","Karl","Kitty","Lewis","Lisa","Maud","Muffin","Neil","Nina","Orion","Oleg","Pringles","Pat","Qubert","Quinton","Rin","Red","Slim","Salty","Trevor","Tarn","Ully","Uber","Vicky","Vanity","Walter","Winston","Xena","Xol","Yury","Yohn","Zina","Zeb"};
 char lastnames[][20] = {"Anderson","Adams","Bean","Boolean","Chops","Chainy","Dickinson","Dell","Eckert","Edgy","Finnegan","Flaps","Gaucho","Gripes","Holly","Hummings","Illsy","Innenko","Jumangee","Junkers","Karlsberg","Kombat","Light","Lee","Manning","Middlebar","Nouny","Nedges","O'Hara","Okonogi","Parcel","Phish","Qurellon","Qube","Read","Ronkels","Sapp","Stonefoot","Tilley","Tron","Unts","Ukkonen","Vindel","Voehr","Wellsharp","Warmiss","Xanadu","Xuzerty","Yuddick","Yompara","Zebulon","Zeffer"};
 
 
 
 char abilities[][20] = {"No ability",
 "Heal",
 "Shield",
 "Hell's heart",
 "Distract",
 "Convert",
 "Mimic",
 "Confuse",
 "Untouchable",
 "Poison",
 "Outmaneuver",
 "Erase"};
 
 int ability_effects[] = {SPECIAL,
 BENEFIT,
 BENEFIT,
 SPECIAL,
 HARM,
 SPECIAL,
 HARM,
 HARM,
 SPECIAL,
 HARM,
 SPECIAL,
 HARM};
 
 int ability_multihit[] = {SINGLE,
 MULTI,
 MULTI,
 SINGLE,
 MULTI,
 SINGLE,
 SINGLE,
 MULTI,
 SINGLE,
 MULTI,
 SINGLE,
 MULTI};
 char pos_targets[][20] = {"Self","Random","All"};
 char neg_targets[][20] = {"Self","Random","All"};
 char pos_who_targets[][20] = {""};
 #endif