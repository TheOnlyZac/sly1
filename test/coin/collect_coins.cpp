#include <coin.h>
#include <gs.h>
#include "../test.h"

int main()
{
	COIN coin;

	// Test collecting a coin normally
	g_pgsCur->ccoin = 0;
	g_pgsCur->ccharm = 0;
	OnCoinSmack(&coin);

	JtAssert(g_pgsCur->ccoin == 1);
	JtAssert(g_pgsCur->ccharm == 0);

	g_pgsCur->ccoin = 98;
	OnCoinSmack(&coin);

	JtAssert(g_pgsCur->ccoin == 99);
	JtAssert(g_pgsCur->ccharm == 0);

	// Test collecting a 100 coins to get a charm
	OnCoinSmack(&coin);

	JtAssert(g_pgsCur->ccoin == 0);
	JtAssert(g_pgsCur->ccharm == 1);

	// Test collecting 100 coins to get an extra life
	g_pgsCur->ccoin = 99;
	g_pgsCur->ccharm = 2;
	g_pgsCur->clife = 5;
	OnCoinSmack(&coin);

	JtAssert(g_pgsCur->ccoin == 0);
	JtAssert(g_pgsCur->ccharm == 2);
	JtAssert(g_pgsCur->clife == 6);

	// Test collecting a coin when coins, lives, and charms are all at max
	g_pgsCur->ccoin = 99;
	g_pgsCur->ccharm = 2;
	g_pgsCur->clife = 99;
	OnCoinSmack(&coin);

	JtAssert(g_pgsCur->ccoin == 99);
	JtAssert(g_pgsCur->ccharm == 2);
	JtAssert(g_pgsCur->clife == 99);
}
