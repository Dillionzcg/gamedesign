#include "FirstEnter.h"

int showTitle() {
    Refresh();
    // ==================== 标题 ====================

    cout << DARK_GOLD;
    cout << "\n ===================================================================================================" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "         #         #              #                  ##                                  #         ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "       ###       ###              ##                ##                                   ##        ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "      ##        ##                  #             #  #         #      #              #########     ";
    cout << DARK_GOLD   << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "   #     ##   #    ##     ##################         #         ##     #               #     #      ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "                              #         #        ########  #    #    #        #     ###########    ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "      #           #            #       #            ##      #       #       #####    #########     ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "    ##       ########           #    #             # ##     #      #          #      # ##### #     ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "  ##  #           #               ##              #  #  #    #    #           #      #########     ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "      #     ##    #                #             #   #     #  #  #  #      #######    #    #       ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "      #      #    #              #  #           #    #   ##    ##   ##                #    #       ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "      #           #            #      #              #   #    #  #     #             #      #   #  ";
    cout << DARK_GOLD << "|" << endl;

    cout << "|";
    cout << RED_DARK;
    cout << "      #          ##         ##          ###          #     ##     ######          ###        ###   ";
    cout << DARK_GOLD << "|" << endl;

    cout << DARK_GOLD;
    cout << " ===================================================================================================" << endl;


    // ==================== 游戏模式 ====================

    cout << endl;
    cout << GOLD_BOLD;
    cout << endl;

    // 三个模式横向排列
    cout << "                   ╔══════════════╗    ╔══════════════╗    ╔══════════════╗" << endl;

    cout << WHITE;
    cout << "                   ║ 1. 普通模式  ║    ║ 2. 困难模式  ║    ║ 3. 继续游戏  ║" << endl;

    cout << GOLD_BOLD;
    cout << "                   ╚══════════════╝    ╚══════════════╝    ╚══════════════╝" << endl;


    // ==================== 游戏简介 ====================

    cout << endl;
    cout << RED_BOLD;
    cout << "    \"Als sich der Riss im Nichts schloss, wurden die Runen zum einzigen letzten Wort der Welt.\"" << endl;
    cout << "                       (当裂隙在虚空中闭合，符文便成了世界唯一的遗言。)" << endl;
    cout << endl;
    cout << "                  浮空秘境的残垣断壁间，失控的符文正无声地剥离着万物的生息。" << endl;
    cout << "                 无人知晓深渊之下还沉睡着什么，唯有石碑上的血迹在无声地延伸。" << endl;



    // ==================== 输入 ====================


    cout << endl;
    cout  << endl;
    cout << WHITE;
    cout << "  请选择游戏模式( " << RED_WINE << "将窗口全屏以获得最佳游戏体验" << WHITE << ")：";
    int TitleChoice;
    TitleChoice = Safecin({ 1, 2, 3 }, false);
    cout << WHITE;
    return TitleChoice;

}



