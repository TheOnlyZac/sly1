u#include <coin.h>
#include <gs.h>

#include <cassert>

int main()
{
	COIN coin;

	// Test collecting a coin normally
	g_pgsCur->c_coins = 0;
	g_pgsCur->c_charms = 0;
	OnCoinSmack(&coin);

	assert(g_pgsCur->c_coins == 1);
	assert(g_pgsCur->c_charms == 0);

	g_pgsCur->c_coins = 98;
	OnCoinSmack(&coin);

	assert(g_pgsCur->c_coins == 99);
	assert(g_pgsCur->c_charms == 0);

	// Test collecting a 100 coins to get a charm
	OnCoinSmack(&coin);

	assert(g_pgsCur->c_coins == 0);
	assert(g_pgsCur->c_charms == 1);

	// Test collecting 100 coins to get an extra life
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_charms = 2;
	g_pgsCur->c_lives = 5;
	OnCoinSmack(&coin);

	assert(g_pgsCur->c_coins == 0);
	assert(g_pgsCur->c_charms == 2);
	assert(g_pgsCur->c_lives == 6);

	// Test collecting a coin when coins, lives, and charms are all at max
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_charms = 2;
	g_pgsCur->c_lives = 99;
	OnCoinSmack(&coin);

	assert(g_pgsCur->c_coins == 99);
	assert(g_pgsCur->c_charms == 2);
	assert(g_pgsCur->c_lives == 99);
}
