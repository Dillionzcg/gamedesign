#include "basis.h"
//void showTitle() {
//    // 红色标题
//    cout << GOLD_BOLD;
//    cout << "\n ======================================  《符文秘境》  =============================================" << endl;
//    cout << GOLD_BOLD;
//    cout << "|";
//    cout << RED_BOLD;
//    cout << "         #         #              #                  ##                                  #         ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "       ###       ###              ##                ##                                   ##        ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "      ##        ##                  #             #  #         #      #              #########     ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "   #     ##   #    ##     ##################         #         ##     #               #     #      ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "                              #         #        ########  #    #    #        #     ###########    ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "      #           #            #       #            ##      #       #       #####    #########     ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "    ##       ########           #    #             # ##     #      #          #      # ##### #     ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "  ##  #           #               ##              #  #  #    #    #           #      #########     ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "      #     ##    #                #             #   #     #  #  #  #      #######    #    #       ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "      #      #    #              #  #           #    #   ##    ##   ##                #    #       ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "      #           #            #      #              #   #    #  #     #             #      #   #  ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl << "|";
//    cout << RED_BOLD;
//    cout << "      #          ##         ##          ###          #     ##     ######          ###        ###   ";
//    cout << GOLD_BOLD;
//    cout << "|" << endl;
//    // 金色副标题
//    cout<<GOLD_BOLD;  // 黄色
//    cout << " ======================================  《符文秘境》  =============================================" << endl;
//
//    // 恢复默认颜色（白色)
//    cout << WHITE;
//    cout << "\n游戏简介：浮空秘境的残垣断壁间，失控的符文正无声地剥离着万物的生息。\n无人知晓深渊之下还沉睡着什么，唯有石碑上的血迹在无声地延伸。" << endl;
//    cout << "1.普通模式          2.困难模式        3.继续游戏 " << endl;
//    cout << "请选择游戏模式:";
//    Safecin({ 1, 2, 3 }, false);
//}
void showTitle() {
    // ==================== 标题 ====================

    cout << QING;
    cout << "\n ===================================================================================================" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "         #         #              #                  ##                                  #         ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "       ###       ###              ##                ##                                   ##        ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "      ##        ##                  #             #  #         #      #              #########     ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "   #     ##   #    ##     ##################         #         ##     #               #     #      ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "                              #         #        ########  #    #    #        #     ###########    ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "      #           #            #       #            ##      #       #       #####    #########     ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "    ##       ########           #    #             # ##     #      #          #      # ##### #     ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "  ##  #           #               ##              #  #  #    #    #           #      #########     ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "      #     ##    #                #             #   #     #  #  #  #      #######    #    #       ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "      #      #    #              #  #           #    #   ##    ##   ##                #    #       ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "      #           #            #      #              #   #    #  #     #             #      #   #  ";
    cout << QING << "|" << endl;

    cout << "|";
    cout << RED_BOLD;
    cout << "      #          ##         ##          ###          #     ##     ######          ###        ###   ";
    cout << QING << "|" << endl;

    cout << QING;
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

    cout << "                       \"当裂隙在虚空中闭合，符文便成了世界唯一的遗言。\"" <<endl;
    cout << "                   浮空秘境的残垣断壁间，失控的符文正无声地剥离着万物的生息。" << endl;
    cout << "                  无人知晓深渊之下还沉睡着什么，唯有石碑上的血迹在无声地延伸。" <<endl;



    // ==================== 输入 ====================

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << HUI;
    cout << "  请选择游戏模式：";
    cout << WHITE;

    Safecin({ 1, 2, 3 }, false);


}



