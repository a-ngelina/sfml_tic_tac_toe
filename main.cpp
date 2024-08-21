#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/System/Vector2.hpp>
#include<string>
#include<iostream>
#include<vector>

#include"button.h"

int getRow(const int y);
int getColumn(const int x);
int isAWin(std::vector<std::vector<Button>>& board_buttons);
void clearBoard(std::vector<std::vector<Button>>& board_buttons, char& curr_player);


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "tic tac toe game", sf::Style::Close | sf::Style::Titlebar);
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("./Font Monument.ttf");
    sf::Time dt = clock.getElapsedTime();
    std::string player1 = "player1", player2 = "player2";
    

    //drawing the board
    Button player1_button(sf::Vector2f(250, 10), sf::Vector2f(350, 70), sf::Color::Black, player1, font, 50, sf::Vector2f(255, 10), sf::Color::White);
    player1_button.getShape().setOutlineThickness(3);
    player1_button.getShape().setOutlineColor(sf::Color::White);

    Button player2_button(sf::Vector2f(680, 10), sf::Vector2f(350, 70), sf::Color::Black, player2, font, 50, sf::Vector2f(685, 10), sf::Color::White);
    player2_button.getShape().setOutlineThickness(3);
    player2_button.getShape().setOutlineColor(sf::Color::White);

    Button board_button(sf::Vector2f(400, 200), sf::Vector2f(490, 490), sf::Color::White, "", font, 0, sf::Vector2f(0, 0), sf::Color::Black);
    Button board_button00(sf::Vector2f(400, 200), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(440, 130), sf::Color::White);
    Button board_button01(sf::Vector2f(565, 200), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(605, 130), sf::Color::White);
    Button board_button02(sf::Vector2f(730, 200), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(770, 130), sf::Color::White);
    Button board_button10(sf::Vector2f(400, 365), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(440, 295), sf::Color::White);
    Button board_button11(sf::Vector2f(565, 365), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(605, 295), sf::Color::White);
    Button board_button12(sf::Vector2f(730, 365), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(770, 295), sf::Color::White);
    Button board_button20(sf::Vector2f(400, 530), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(440, 460), sf::Color::White);
    Button board_button21(sf::Vector2f(565, 530), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(605, 460), sf::Color::White);
    Button board_button22(sf::Vector2f(730, 530), sf::Vector2f(160,160), sf::Color::Black, "", font, 200, sf::Vector2f(770, 460), sf::Color::White);

    Button reset_score_button(sf::Vector2f(950, 625), sf::Vector2f(120, 60), sf::Color::White, "reset\nscore", font, 30, sf::Vector2f(980, 620), sf::Color::Black);
    Button reset_board_button(sf::Vector2f(1100, 625), sf::Vector2f(120, 60), sf::Color::White, "reset\nboard", font, 30, sf::Vector2f(1125, 620), sf::Color::Black);

    std::vector<std::vector<Button>> board_buttons = {{board_button00, board_button01, board_button02}, {board_button10, board_button11, board_button12}, {board_button20, board_button21, board_button22}};
    std::vector<Button> buttons = {player1_button, player2_button, board_button, reset_score_button, reset_board_button};


    sf::Text score1_text("0", font, 80);
    score1_text.setPosition(500, 100);

    sf::Text colon(":", font, 80);
    colon.setPosition(635, 100);

    sf::Text score2_text("0", font, 80);
    score2_text.setPosition(750, 100);

    sf::Text winner_text("", font, 50);
    winner_text.setPosition(sf::Vector2f(950, 500));


    int score1 = 0, score2 = 0;
    char curr_player = 'x';
    bool reading_player1 = 0, reading_player2 = 0;

    

    while (window.isOpen()) {
        sf::Event event;

        
        //closing the window
        while (window.pollEvent(event)) {
            if (event.type == event.Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                reading_player1 = 0, reading_player2 = 0;
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

                //the score needs to be reset
                if (reset_score_button.ButtonClicked(mouse_position)) {
                    score1 = 0, score2 = 0;
                    clearBoard(board_buttons, curr_player);
                    score1_text.setString(std::to_string(score1));
                    score2_text.setString(std::to_string(score2));
                }

                //the booard needs to be reset
                else if (reset_board_button.ButtonClicked(mouse_position)) {
                    clearBoard(board_buttons, curr_player);
                }

                //board clicked
                else if (board_button.ButtonClicked(mouse_position)) {
                    int i = getRow(mouse_position.y), j = getColumn(mouse_position.x);
                    if (i >= 0 && j >= 0 && board_buttons[i][j].getLabel().getString() != "x" && board_buttons[i][j].getLabel().getString() != "o") {
                        board_buttons[i][j].getLabel().setString(curr_player == 'x' ? "x" : "o");
                        int win = isAWin(board_buttons);
                        if (win == -1) {
                            int cnt = 0;
                            for (std::vector<Button>& row: board_buttons) {
                                for (Button& button: row) cnt += (button.getLabel().getString() == "x" || button.getLabel().getString() == "o");
                            }
                            if (cnt == 9) {
                                score1++, score2++;
                                dt = clock.restart();
                                winner_text.setString("draw!");
                                clearBoard(board_buttons, curr_player);
                            }
                            else curr_player = (curr_player == 'x' ? 'o' : 'x');
                        }
                        else {
                            dt = clock.restart();
                            if (win == 1) score1++, winner_text.setString(player1 + "\nwins!");
                            else score2++, winner_text.setString(player2 + "\nwins!");
                            clearBoard(board_buttons, curr_player);
                        }

                    }
                    score1_text.setString(std::to_string(score1));
                    score2_text.setString(std::to_string(score2));
                }
                
                //reading player usernames
                else if (player1_button.ButtonClicked(mouse_position)) reading_player1 = 1;
                else if (player2_button.ButtonClicked(mouse_position)) reading_player2 = 1;
            }

            //reading player usernames
            else if (reading_player1 == 1 || reading_player2 == 1) {
                Button& curr_button = (reading_player1 == 1 ? buttons[0] : buttons[1]);
                std::string& curr_str_player = (reading_player1 == 1 ? player1 : player2);
                if (event.type == sf::Event::TextEntered && event.text.unicode >= 32 && event.text.unicode <= 126) curr_str_player += event.text.unicode, curr_button.getLabel().setString(curr_str_player);
                else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace) {
                    if (curr_str_player.length() > 0) curr_str_player.pop_back(), curr_button.getLabel().setString(curr_str_player);
                }
            }
        }

        window.clear();
        for (Button button: buttons) {
            window.draw(button.getShape());
            window.draw(button.getLabel());
        }
        for (std::vector<Button>& row: board_buttons) {
            for (Button& button: row) {
                window.draw(button.getShape());
                window.draw(button.getLabel());
            }
        }
        window.draw(colon);
        window.draw(score1_text);
        window.draw(score2_text);
        if (clock.getElapsedTime().asSeconds() <= 3.0) {
            window.draw(winner_text);
        }
        window.display();
    }
    return 0;
}

int getRow(const int y) {
    if (y <= 360) return 0;
    else if (y >= 365 && y <= 525) return 1;
    else if (y >= 530 && y <= 690) return 2;
    else return -1;
}
int getColumn(const int x) {
    if (x <= 560) return 0;
    else if (x >= 565 && x <= 725) return 1;
    else if (x >= 730 && x <= 890) return 2;
    else return -1;
}
int isAWin(std::vector<std::vector<Button>>& board_buttons) {
    sf::String row0 = board_buttons[0][0].getLabel().getString() + board_buttons[0][1].getLabel().getString() + board_buttons[0][2].getLabel().getString(), row1 = board_buttons[1][0].getLabel().getString() + board_buttons[1][1].getLabel().getString() + board_buttons[1][2].getLabel().getString(), row2 = board_buttons[2][0].getLabel().getString() + board_buttons[2][1].getLabel().getString() + board_buttons[2][2].getLabel().getString(), column0 = board_buttons[0][0].getLabel().getString() + board_buttons[1][0].getLabel().getString() + board_buttons[2][0].getLabel().getString(), column1 = board_buttons[0][1].getLabel().getString() + board_buttons[1][1].getLabel().getString() + board_buttons[2][1].getLabel().getString(), column2 = board_buttons[0][2].getLabel().getString() + board_buttons[1][2].getLabel().getString() + board_buttons[2][2].getLabel().getString(), diagonal0 = board_buttons[0][0].getLabel().getString() + board_buttons[1][1].getLabel().getString() + board_buttons[2][2].getLabel().getString(), diagonal1 = board_buttons[0][2].getLabel().getString() + board_buttons[1][1].getLabel().getString() + board_buttons[2][0].getLabel().getString();
    if (row0 == "xxx" || row1 == "xxx" || row2 == "xxx" || column0 == "xxx" || column1 == "xxx" || column2 == "xxx" || diagonal0 == "xxx" || diagonal1 == "xxx") return 1;
    else if (row0 == "ooo" || row1 == "ooo" || row2 == "ooo" || column0 == "ooo" || column1 == "ooo" || column2 == "ooo" || diagonal0 == "ooo" || diagonal1 == "ooo") return 2;
    return -1;
}
void clearBoard(std::vector<std::vector<Button>>& board_buttons, char& curr_player) {
    curr_player = 'x';
    for (std::vector<Button>& row: board_buttons) {
        for (Button& button: row) button.getLabel().setString("");
    }
}