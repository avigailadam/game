#include <gtest/gtest.h>

#include "Auxiliaries.h"

#include "Game.h"

class GameFixture: public ::testing::Test {
public:
    // Initialization
    GameFixture() : game{HEIGHT, WIDTH} { }

    // Teardown
    virtual ~GameFixture() = default;

    // Per-test setup
    void SetUp() override {
        game = mtm::Game{HEIGHT, WIDTH};
        const auto character1 = game.makeCharacter(mtm::CharacterType::SOLDIER, mtm::Team::CROSSFITTERS, 1, 2, 3, 4);
        game.addCharacter(mtm::GridPoint{1, 1}, character1);
        const auto character2 = game.makeCharacter(mtm::CharacterType::SNIPER, mtm::Team::CROSSFITTERS, 1, 2, 3, 4);
        game.addCharacter(mtm::GridPoint{1, 2}, character2);
    }

    // Per-test cleanup
    void TearDown() override {
    }

    static const int HEIGHT = 10;
    static const int WIDTH = 20;
    mtm::Game game;
};

TEST_F(GameFixture, CellIsAlreadyTaken) {
    EXPECT_THROW(game.addCharacter(mtm::GridPoint{1, 1}, std::shared_ptr<mtm::Character>()), mtm::CellOccupied);
}

TEST(Game, CopyClonesCharacters) {
    mtm::Game game{3, 3};
    const auto character = game.makeCharacter(mtm::CharacterType::SOLDIER, mtm::Team::CROSSFITTERS, 1, 1, 1, 1);
    const auto location = mtm::GridPoint{0, 0};
    game.addCharacter(location, character);
    // EXPECT_EQ(character, /* character at location */);
    // mtm::Game duplicate{game};
    // EXPECT_EQ(character, /* character at location */);
    // EXPECT_NE(/* duplicate's characer at location */, character.get());
//    EXPECT_TRUE(false);
}
