#pragma once

/**
 * @brief Coin prize
*/
struct COIN
{
	// todo: add struct fields
	int padding[0x3ac];
};

/**
 * @brief Initializes a coin.
 *
 * @param pcoin Pointer to the coin.
 *
 * @return 0 on success; nonzero on failure.
 *
 * @todo Implement this function.
 */
//int InitCoin(Coin* pcoin);

/**
 * @brief Handles when the player touches a coin.
 *
 * @param pcoin Pointer to the coin.
 */
void OnCoinSmack(COIN* pcoin);

/**
 * @brief Sets the coin's prize.
 *
 * @param pcoin Pointer to the coin.
 * @param dprizes The new prize.
 *
 * @todo Implement this function.
 */
//void SetcoinDprizes(Coin* pcoin, Dprizes dprizes);

/**
 * @brief Updates the coin.
 *
 * @param pcoin Pointer to the coin.
 * @param dt Time elapsed since the last frame.
 *
 * @todo Implement this function.
 */
//void UpdateCoin(Coin* pcoin, float dt);
