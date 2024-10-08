new Float:baza_chilliad_0_field[] =
{
-2795.9167,-1483.2917,
-2789.3796,-1497.9990,
-2789.6934,-1521.5927,
-2793.6301,-1534.2688,
-2798.5176,-1540.4487,
-2804.8647,-1545.4401,
-2820.5618,-1542.8744,
-2827.6770,-1539.2548,
-2830.6528,-1531.7598,
-2833.7107,-1500.3873,
-2831.4001,-1493.3645,
-2827.4260,-1486.7882,
-2819.9531,-1482.8586
};

stock baza_chilliad_0()
{
	baza[0][b_active] = true;
	baza[0][b_price] = 2000;

	baza[0][b_pickup][0] = -2789.6362;
	baza[0][b_pickup][1] = -1526.7725;
	baza[0][b_pickup][2] = 139.3137;

	baza[0][b_magazyn][0] = -2808.8040;
	baza[0][b_magazyn][1] = -1491.4395;
	baza[0][b_magazyn][2] = 140.6217;

	baza[0][b_gate_model] = 19908;

	baza[0][b_gate_close][0] = -2793.23242;
	baza[0][b_gate_close][1] = -1531.37524;
	baza[0][b_gate_close][2] = 140.77950;
	baza[0][b_gate_close][3] = 0.0;
	baza[0][b_gate_close][4] = 0.0;
	baza[0][b_gate_close][5] = 343.01059;

	baza[0][b_gate_open][0] = -2791.76367;
	baza[0][b_gate_open][1] = -1526.10364;
	baza[0][b_gate_open][2] = 140.77950;
	baza[0][b_gate_open][3] = 0.0;
	baza[0][b_gate_open][4] = 0.0;
	baza[0][b_gate_open][5] = 343.01059;

	baza[0][b_area_id] = CreateDynamicPolygon(baza_chilliad_0_field);

	CreateDynamicObject(19641, -2796.41797, -1537.06262, 138.43710,   0.00000, 0.00000, 51.62280);
	CreateDynamicObject(18259, -2816.19336, -1491.66248, 139.53581,   0.00000, 0.00000, 88.77789);
	CreateDynamicObject(19641, -2802.03223, -1542.62061, 138.55341,   0.00000, 2.00000, 38.00000);
	CreateDynamicObject(19641, -2808.87305, -1544.34412, 138.64713,   0.00000, 0.00000, 350.61420);
	CreateDynamicObject(19641, -2816.56299, -1543.07104, 138.64709,   0.00000, 0.00000, 350.61420);
	CreateDynamicObject(19641, -2823.85815, -1540.67969, 138.54109,   0.00000, -2.00000, 333.00000);
	CreateDynamicObject(19641, -2828.86304, -1535.19141, 138.25610,   0.00000, 3.00000, 110.71360);
	CreateDynamicObject(19641, -2830.68848, -1527.51538, 137.95010,   0.00000, 1.00000, 95.32910);
	CreateDynamicObject(19641, -2831.41235, -1519.75793, 137.81410,   0.00000, 1.00000, 95.32910);
	CreateDynamicObject(19641, -2832.15137, -1511.89355, 137.74809,   0.00000, -0.30000, 95.32910);
	CreateDynamicObject(19641, -2832.87866, -1504.15686, 137.72411,   0.00000, 0.00000, 95.32910);
	CreateDynamicObject(19641, -2831.96582, -1496.58838, 137.63409,   0.00000, 1.20000, 70.84790);
	CreateDynamicObject(19641, -2828.98584, -1490.24060, 137.50810,   0.00000, 2.00000, 58.86311);
	CreateDynamicObject(19641, -2791.31006, -1525.11926, 138.23511,   0.00000, 1.50000, 72.92392);
	CreateDynamicObject(19641, -2790.08618, -1517.50500, 138.05310,   0.00000, 1.70000, 89.43910);
	CreateDynamicObject(19641, -2790.01489, -1509.71155, 137.74510,   0.00000, 1.80000, 89.43910);
	CreateDynamicObject(19641, -2789.91992, -1501.90930, 137.50110,   0.00000, 1.80000, 89.43910);
	CreateDynamicObject(19641, -2791.48145, -1494.29883, 137.30112,   0.00000, 0.00000, 114.12650);
	CreateDynamicObject(19641, -2794.66333, -1487.18469, 137.30112,   0.00000, 0.00000, 114.12650);
	CreateDynamicObject(19641, -2800.33936, -1483.55750, 137.39908,   0.00000, -3.00000, 179.30110);
	CreateDynamicObject(19641, -2808.11328, -1483.46680, 137.60913,   0.00000, -1.00000, 179.30110);
	CreateDynamicObject(19641, -2815.86133, -1483.38416, 137.51910,   0.00000, 2.00000, 179.30110);
	CreateDynamicObject(19641, -2823.42065, -1485.05505, 137.37711,   0.00000, 0.00000, 206.18030);
	return 1;
}