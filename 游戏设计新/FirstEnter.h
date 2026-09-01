#include "basis.h"
void showTitle() {
    // 红色标题
    cout << GOLD_BOLD;
    cout << "\n ======================================  《符文秘境》  =============================================" << endl;
    cout << GOLD_BOLD;
    cout << "|";
    cout << RED_BOLD;
    cout << "         #         #              #                  ##                                  #         ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "       ###       ###              ##                ##                                   ##        ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "      ##        ##                  #             #  #         #      #              #########     ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "   #     ##   #    ##     ##################         #         ##     #               #     #      ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "                              #         #        ########  #    #    #        #     ###########    ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "      #           #            #       #            ##      #       #       #####    #########     ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "    ##       ########           #    #             # ##     #      #          #      # ##### #     ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "  ##  #           #               ##              #  #  #    #    #           #      #########     ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "      #     ##    #                #             #   #     #  #  #  #      #######    #    #       ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "      #      #    #              #  #           #    #   ##    ##   ##                #    #       ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "      #           #            #      #              #   #    #  #     #             #      #   #  ";
    cout << GOLD_BOLD;
    cout << "|" << endl << "|";
    cout << RED_BOLD;
    cout << "      #          ##         ##          ###          #     ##     ######          ###        ###   ";
    cout << GOLD_BOLD;
    cout << "|" << endl;
    // 金色副标题
    cout<<GOLD_BOLD;  // 黄色
    cout << " ======================================  《符文秘境》  =============================================" << endl;

    // 恢复默认颜色（白色)
    cout << WHITE;
    cout << "\n游戏简介：这是一款在控制台（黑窗口） 中运行的单人文字冒险游戏。你将从三名英雄中选择一位，踏入由文字描绘的符文大陆，在四个章节中探索、战斗、成长，最终击败王者峡谷的主宰，成为传说。" << endl;
    cout << "1.普通模式          2.困难模式        3.继续游戏 " << endl;
    cout << "请选择游戏模式:";
    Safecin({ 1, 2, 3 }, false);
}

