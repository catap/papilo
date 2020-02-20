/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*               This file is part of the program and library                */
/*    PaPILO --- Parallel Presolve for Integer and Linear Optimization       */
/*                                                                           */
/* Copyright (C) 2020  Konrad-Zuse-Zentrum                                   */
/*                     fuer Informationstechnik Berlin                       */
/*                                                                           */
/* This program is free software: you can redistribute it and/or modify      */
/* it under the terms of the GNU Lesser General Public License as published  */
/* by the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>.    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "papilolib.h"
#include "catch/catch.hpp"
#include "papilo/misc/fmt.hpp"

TEST_CASE( "papilolib", "[C-API]" )
{
   constexpr int num_facilities = 25;
   constexpr int num_customers = 50;

   double facility_fixcost[] = {
       7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0,
       7500.0, 0.0,    7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0,
       7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0, 7500.0};

   double facility_capacity[] = {58268.0, 58268.0, 58268.0, 58268.0, 58268.0,
                                 58268.0, 58268.0, 58268.0, 58268.0, 58268.0,
                                 58268.0, 58268.0, 58268.0, 58268.0, 58268.0,
                                 58268.0, 58268.0, 58268.0, 58268.0, 58268.0,
                                 58268.0, 58268.0, 58268.0, 58268.0, 58268.0};
   double customer_demand[] = {
       146.0,  87.0,   672.0, 1337.0, 31.0,   559.0,  2370.0,  1089.0, 33.0,
       32.0,   5495.0, 904.0, 1466.0, 143.0,  615.0,  564.0,   226.0,  3016.0,
       253.0,  195.0,  38.0,  807.0,  551.0,  304.0,  814.0,   337.0,  4368.0,
       577.0,  482.0,  495.0, 231.0,  322.0,  685.0,  12912.0, 325.0,  366.0,
       3671.0, 2213.0, 705.0, 328.0,  1681.0, 1117.0, 275.0,   500.0,  2241.0,
       733.0,  222.0,  49.0,  1464.0, 222.0};

   double facility_customer_service_cost[num_facilities][num_customers] = {
       {6739.72500,   3204.86250,   4914.00000,  32372.11250,  1715.46250,
        6421.51250,   81972.37500,  33391.46250, 2020.83750,   1459.60000,
        141015.43750, 17684.50000,  38207.62500, 1953.73750,   17181.56250,
        25640.85000,  7031.42500,   78453.70000, 9452.71250,   8597.06250,
        1581.27500,   23170.98750,  12087.56250, 4883.00000,   24063.87500,
        4124.03750,   281463.00000, 11056.76250, 8585.62500,   12480.18750,
        3727.76250,   4673.02500,   13451.68750, 372672.60000, 9745.93750,
        12055.12500,  97602.71250,  60774.51250, 54470.06250,  7146.30000,
        38011.61250,  39723.31250,  16111.56250, 16981.25000,  168663.26250,
        57109.86250,  15576.07500,  2542.48750,  34056.30000,  7095.67500},
       {10355.05000,  5457.07500,   26409.60000, 29982.22500,  2152.17500,
        23701.60000,  28499.25000,  26544.37500, 2480.77500,   1995.20000,
        205925.12500, 32069.40000,  42477.35000, 5044.32500,   36054.37500,
        35602.50000,  10492.05000,  92515.80000, 12441.27500,  14113.12500,
        2030.15000,   48702.45000,  19877.32500, 12851.60000,  39682.50000,
        12148.85000,  406770.00000, 22113.52500, 22449.15000,  25455.37500,
        11116.87500,  13346.90000,  35106.25000, 229188.00000, 18070.00000,
        18181.05000,  73603.55000,  63568.42500, 65177.25000,  8618.20000,
        70728.07500,  52917.87500,  20714.37500, 32575.00000,  210766.05000,
        66703.00000,  18481.50000,  3928.57500,  34221.00000,  11999.10000},
       {7650.40000,   3845.40000,   19622.40000, 21024.32500,  1577.90000,
        16197.02500,  43134.00000,  6370.65000,  1869.45000,   1402.40000,
        104130.25000, 15322.80000,  15319.70000, 4089.80000,   25399.50000,
        25154.40000,  6305.40000,   36644.40000, 7754.45000,   10500.75000,
        1326.20000,   36072.90000,  9670.05000,  10822.40000,  24603.15000,
        8180.67500,   325852.80000, 11424.60000, 14122.60000,  22151.25000,
        8229.37500,   7880.95000,   25927.25000, 203364.00000, 12049.37500,
        11400.90000,  59561.97500,  27330.55000, 52117.12500,  6428.80000,
        39587.55000,  32225.45000,  15620.00000, 23312.50000,  169251.52500,
        53124.17500,  14368.95000,  3020.85000,  24448.80000,  7886.55000},
       {5219.50000,  2396.85000,   13876.80000, 29681.40000,  1061.75000,
        10383.42500, 65767.50000,  16770.60000, 1324.95000,   869.60000,
        12638.50000, 8429.80000,   15832.80000, 3428.42500,   16297.50000,
        15763.80000, 2542.50000,   27445.60000, 3542.00000,   7254.00000,
        693.50000,   26166.97500,  3801.90000,  8930.00000,   11050.05000,
        5611.05000,  253234.80000, 5582.47500,  7458.95000,   19069.87500,
        5826.97500,  4330.90000,   17347.62500, 322800.00000, 7198.75000,
        5307.00000,  83331.70000,  30982.00000, 40378.87500,  7822.80000,
        15801.40000, 13627.40000,  11041.25000, 16250.00000,  131938.87500,
        40919.72500, 10672.65000,  2205.00000,  31329.60000,  4190.25000},
       {5776.12500,  2628.48750,   9147.60000,  21275.01250,  1250.46250,
        7483.61250,  58805.62500,  13571.66250, 1525.83750,   1050.80000,
        46089.31250, 1231.70000,   11526.42500, 2289.78750,   15828.56250,
        18421.65000, 3918.27500,   23562.50000, 5082.13750,   7875.56250,
        924.82500,   23493.78750,  2252.21250,  6798.20000,   13644.67500,
        2952.96250,  264755.40000, 2430.61250,  6609.42500,   15598.68750,
        4628.66250,  2861.77500,   15249.81250, 261306.60000, 7592.81250,
        7379.47500,  65940.33750,  20497.91250, 44494.31250,  5211.10000,
        16494.81250, 20427.13750,  12598.43750, 16268.75000,  144628.53750,
        45381.86250, 12024.07500,  2361.18750,  21905.10000,  4847.92500},
       {6641.17500,  3220.08750,   14977.20000, 20071.71250,  1363.61250,
        12332.93750, 48555.37500,  8861.73750,  1646.28750,   1181.20000,
        66146.06250, 9073.90000,   5185.97500,  3530.31250,   21148.31250,
        21255.75000, 4743.17500,   23034.70000, 6005.58750,   9152.81250,
        1063.52500,  30494.51250,  5847.48750,  9435.40000,   18976.37500,
        5851.16250,  294457.80000, 7436.08750,  10790.77500,  19892.81250,
        6632.58750,  5655.12500,   21192.18750, 229995.00000, 9802.81250,
        8870.92500,  56946.38750,  15076.06250, 47243.81250,  5621.10000,
        27925.61250, 24504.18750,  13719.06250, 19856.25000,  153760.61250,
        48057.31250, 12834.37500,  2682.13750,  20807.10000,  6351.97500},
       {4374.52500,   1838.96250,   21848.40000,  64292.98750,  1524.03750,
        15840.66250,  138615.37500, 51550.53750,  1817.06250,   1133.20000,
        198300.81250, 32781.30000,  62653.17500,  5553.76250,   7310.81250,
        18478.05000,  6856.27500,   126332.70000, 10274.96250,  5467.31250,
        1628.77500,   14919.41250,  19650.03750,  11943.40000,  20197.37500,
        11613.86250,  211356.60000, 19279.01250,  11525.82500,  23976.56250,
        6476.66250,   9623.77500,   16808.18750,  681269.40000, 5780.93750,
        10865.62500,  185247.83750, 97731.61250,  47631.56250,  15256.10000,
        49862.66250,  41119.56250,  12502.18750,  9331.25000,   134768.13750,
        52583.58750,  14205.22500,  1756.03750,   69009.30000,  4903.42500},
       {3847.10000,   2266.35000,   35330.40000,  80186.57500,  955.57500,
        27251.25000,  155294.25000, 57907.57500,  1211.92500,   546.40000,
        220212.12500, 41335.40000,  71210.95000,  8308.30000,   21709.50000,
        8135.70000,   7119.00000,   141375.00000, 10214.87500,  6371.62500,
        1619.75000,   33813.30000,  23844.52500,  18148.80000,  24684.55000,
        17111.17500,  210756.00000, 25460.12500,  20448.85000,  34080.75000,
        11884.95000,  14610.75000,  32845.75000,  810550.80000, 10692.50000,
        10202.25000,  222003.72500, 114578.07500, 34351.12500,  19762.00000,
        62659.27500,  40854.27500,  7885.62500,   20750.00000,  109304.77500,
        39050.57500,  10134.30000,  1983.27500,   86632.20000,  6421.35000},
       {6429.47500,  3117.86250,   15111.60000, 25921.08750,  1318.66250,
        12444.73750, 53176.87500,  10985.28750, 1593.48750,   1134.80000,
        58178.31250, 9254.70000,   11563.07500, 3558.91250,   20779.31250,
        20437.95000, 4415.47500,   11423.10000, 5638.73750,   8870.06250,
        1008.42500,  30655.91250,  6260.73750,  9496.20000,   17796.07500,
        5918.56250,  289434.60000, 7551.48750,  10887.17500,  19991.81250,
        6678.78750,  5719.52500,   21329.18750, 258078.60000, 9607.81250,
        8340.22500,  73007.01250,  24757.93750, 46820.81250,  7047.90000,
        26917.01250, 22884.53750,  13320.31250, 19556.25000,  150511.16250,
        46994.46250, 12512.47500,  2611.08750,  27212.10000,  6030.07500},
       {5396.52500,   2582.81250,   23679.60000,  69206.46250,  1789.08750,
        17769.21250,  147325.12500, 57376.68750,  2099.21250,   1406.80000,
        241573.93750, 37595.10000,  70496.27500,  5947.01250,   12569.06250,
        23300.25000,  8788.57500,   144881.10000, 12438.11250,  6729.93750,
        1953.67500,   11166.86250,  22873.38750,  11616.60000,  27157.07500,
        12852.33750,  239639.40000, 22351.53750,  14092.47500,  23444.43750,
        6101.28750,   11338.42500,  15695.06250,  728398.20000, 8559.68750,
        13994.92500,  198738.76250, 109515.83750, 53659.31250,  16305.70000,
        61965.86250,  50669.91250,  14853.43750,  9543.75000,   149278.61250,
        58814.08750,  16103.32500,  2073.31250,   74352.90000,  6801.52500},
       {5219.50000,  2296.80000,   9828.00000,  23096.67500,  1133.05000,
        7029.42500,  56998.50000,  12741.30000, 1395.90000,   928.80000,
        25277.00000, 2463.40000,   10371.95000, 2434.57500,   14621.62500,
        16271.40000, 3062.30000,   22846.20000, 4123.90000,   7312.50000,
        780.90000,   22333.72500,  0.00000,     7106.00000,   10541.30000,
        3268.90000,  248102.40000, 1601.17500,  5916.55000,   16099.87500,
        4440.97500,  2398.90000,   14693.25000, 261790.80000, 6353.75000,
        5984.10000,  65986.22500,  20525.57500, 42775.87500,  5658.00000,
        10086.00000, 16196.50000,  11550.00000, 14550.00000,  136084.72500,
        42605.62500, 11183.25000,  2174.37500,  23899.80000,  4001.55000},
       {4182.90000,  1779.15000,   19303.20000, 48700.22500,  1015.25000,
        13919.10000, 102384.00000, 33595.65000, 1275.45000,   768.80000,
        97536.25000, 19775.00000,  38482.50000, 4897.75000,   11931.00000,
        12619.50000, 2712.00000,   74042.80000, 5635.57500,   5869.50000,
        931.95000,   20982.00000,  10703.17500, 10898.40000,  5270.65000,
        9073.72500,  222222.00000, 11698.67500, 8953.15000,   22275.00000,
        6843.37500,  6931.05000,   19385.50000, 512606.40000, 4891.25000,
        4154.10000,  137295.40000, 63513.10000, 39250.87500,  11939.20000,
        22567.42500, 20636.57500,  10071.87500, 13087.50000,  124879.72500,
        40553.22500, 10561.65000,  1857.10000,  51935.40000,  2614.05000},
       {7391.25000,   5115.60000,   57472.80000,  135170.70000,  2005.70000,
        45474.65000,  259515.00000, 105796.35000, 1940.40000,    1950.40000,
        461992.12500, 79235.60000,  135275.15000, 13134.55000,   39913.50000,
        35094.90000,  17458.50000,  274079.00000, 21789.62500,   9506.25000,
        3066.60000,   56025.97500,  46945.20000,  28226.40000,   59259.20000,
        29479.07500,  124051.20000, 49650.85000,  37089.90000,   50490.00000,
        18722.55000,  26701.85000,  53121.75000,  1361570.40000, 21336.25000,
        26946.75000,  378755.42500, 209073.17500, 40960.50000,   32644.20000,
        133135.20000, 91957.02500,  13193.12500,  32087.50000,   89976.15000,
        45922.45000,  14940.60000,  2006.55000,   147937.20000,  14979.45000},
       {5038.82500,   2189.13750,   11180.40000, 40527.81250,  1379.88750,
        6966.53750,   96429.37500,  32220.78750, 1663.61250,   1145.20000,
        106122.18750, 16712.70000,  36631.67500, 3283.63750,   11169.93750,
        19253.55000,  5031.32500,   75211.50000, 8073.86250,   6695.81250,
        1298.17500,   17380.76250,  10145.28750, 7117.40000,   14845.32500,
        5623.68750,   238875.00000, 9022.83750,  2958.27500,   16118.43750,
        3693.11250,   3900.22500,   10951.43750, 451435.80000, 5951.56250,
        8459.17500,   119995.81250, 58395.53750, 48318.93750,  9417.70000,
        23134.76250,  31401.66250,  13052.18750, 12481.25000,  142499.58750,
        49175.13750,  13172.92500,  2064.73750,  42986.70000,  4503.82500},
       {10349.57500,  5399.43750,   22957.20000,  60515.96250,  2512.93750,
        20326.63750,  131920.12500, 60071.96250,  2869.76250,   2314.80000,
        288418.81250, 41956.90000,  77569.72500,  4634.98750,   32479.68750,
        39867.75000,  13093.87500,  159433.30000, 16239.43750,  13554.93750,
        2600.62500,   40178.51250,  26881.91250,  7725.40000,   44597.02500,
        13172.48750,  392519.40000, 26549.21250,  20575.37500,  8049.93750,
        8596.08750,   13310.67500,  27888.06250,  644793.00000, 17830.31250,
        21470.47500,  174969.03750, 114439.76250, 73399.31250,  13583.30000,
        81255.33750,  69686.83750,  23103.43750,  27518.75000,  224408.13750,
        75966.28750,  21287.02500,  3788.31250,   64873.50000,  12617.92500},
       {6051.70000,   2838.37500,   15489.60000,  52911.77500,  1823.57500,
        10956.40000,  118381.50000, 46527.52500,  2135.92500,   1500.80000,
        185456.25000, 28589.00000,  55891.25000,  4204.20000,   14375.62500,
        24957.00000,  8294.20000,   114834.20000, 11726.55000,  7707.37500,
        1846.80000,   15978.60000,  17728.42500,  7911.60000,   26495.70000,
        8745.15000,   261534.00000, 16963.80000,  9917.15000,   17411.62500,
        3285.97500,   7961.45000,   7346.62500,   575875.20000, 9514.37500,
        13697.55000,  155375.07500, 87468.82500,  55712.62500,  12308.20000,
        47404.20000,  47528.35000,  15654.37500,  12525.00000,  160511.62500,
        61003.92500,  16755.45000,  2318.92500,   56510.40000,  7448.10000},
       {9568.47500,   4940.51250,   21294.00000, 19804.31250,  2008.41250,
        19446.21250,  37594.12500,  21820.83750, 2327.73750,   1846.80000,
        180442.06250, 26227.30000,  35788.72500, 3955.73750,   31372.68750,
        32986.95000,  9443.97500,   79433.90000, 11267.98750,  13238.06250,
        1853.92500,   42538.98750,  16757.28750, 10537.40000,  35297.07500,
        9583.43750,   380835.00000, 18384.66250, 18779.92500,  21687.18750,
        9358.38750,   10895.67500,  30148.56250, 130895.40000, 16229.68750,
        16483.72500,  45566.28750,  46721.96250, 61907.81250,  6121.30000,
        61209.41250,  47737.78750,  19439.06250, 28893.75000,  200373.41250,
        63303.71250,  17451.97500,  3664.58750,  23076.30000,  10753.12500},
       {9064.77500,   4642.53750,   18992.40000, 15191.66250,  1901.46250,
        17517.66250,  40319.62500,  21085.76250, 2218.83750,   1736.40000,
        161484.31250, 23131.10000,  30731.02500, 3465.96250,   29250.93750,
        31041.15000,  8664.27500,   75663.90000, 10401.46250,  12428.81250,
        1722.82500,   39775.01250,  14856.33750, 9496.20000,   32488.77500,
        8420.78750,   365874.60000, 16408.43750, 17129.07500,  19991.81250,
        8567.21250,   9784.77500,   27802.43750, 145421.40000, 15116.56250,
        15221.02500,  32993.11250,  39142.43750, 59475.56250,  4997.90000,
        55409.96250,  43884.13750,  18490.31250, 27181.25000,  192641.96250,
        60774.86250,  16686.07500,  3495.53750,  18025.50000,  9987.22500},
       {7159.47500,  3507.18750,   16657.20000, 17163.73750,  1497.68750,
        13730.43750, 50569.87500,  12128.73750, 1789.01250,   1318.80000,
        89774.56250, 11333.90000,  11599.72500, 3423.06250,   22701.18750,
        23680.95000, 5714.97500,   36305.10000, 7099.81250,   9845.06250,
        1227.87500,  32512.01250,  7665.78750,  9405.00000,   21866.07500,
        6693.66250,  308872.20000, 8878.58750,  11995.77500,  19843.31250,
        7210.08750,  6460.12500,   22904.68750, 201588.60000, 10875.31250,
        10444.72500, 48961.96250,  10262.78750, 50292.93750,  4907.70000,
        33472.91250, 29335.21250,  14901.56250, 21506.25000,  163396.91250,
        51227.53750, 13794.52500,  2856.08750,  17622.90000,  7090.12500},
       {4781.50000,  2035.80000,   12297.60000, 34762.00000,  1108.25000,
        8371.02500,  78328.50000,  22542.30000, 1374.45000,   832.80000,
        55499.50000, 10350.80000,  23565.95000, 3406.97500,   12776.62500,
        14579.40000, 2599.00000,   45918.60000, 5350.95000,   6547.12500,
        889.20000,   21002.17500,  4959.00000,  7881.20000,   8099.30000,
        5560.50000,  234998.40000, 5683.45000,  5121.25000,   17362.12500,
        4435.20000,  3574.20000,   14025.37500, 377998.80000, 5378.75000,
        4886.10000,  99025.22500,  40442.57500, 40660.87500,  8519.80000,
        5043.00000,  19379.95000,  10725.00000, 13050.00000,  129361.72500,
        42752.22500, 11227.65000,  2072.70000,  36673.20000,  3335.55000},
       {6033.45000,  2890.57500,   23856.00000, 49569.27500,  908.30000,
        18684.57500, 100962.00000, 32942.25000, 1156.65000,   916.00000,
        94239.25000, 21854.20000,  37602.90000, 5551.97500,   19787.62500,
        16581.60000, 3101.85000,   72233.20000, 2795.65000,   8360.62500,
        505.40000,   31291.42500,  11984.25000, 13444.40000,  15669.50000,
        10615.50000, 267212.40000, 14150.92500, 14086.45000,  26420.62500,
        8731.80000,  9112.60000,   26766.37500, 514543.20000, 9051.25000,
        5837.70000,  137846.05000, 63900.37500, 36889.12500,  12693.60000,
        36309.60000, 8098.25000,   11440.00000, 19475.00000,  135188.32500,
        37291.37500, 9573.75000,   2483.07500,  53106.60000,  5450.10000},
       {6661.25000,   3943.27500,   48568.80000,  105288.75000,  1169.47500,
        38375.35000,  199791.00000, 78353.55000,  1050.22500,    1087.20000,
        323380.75000, 59166.80000,  98735.10000,  11125.40000,   33563.62500,
        19881.00000,  11362.15000,  198000.40000, 14964.95000,   10130.25000,
        2041.55000,   49368.22500,  34713.00000,  24198.40000,   41636.10000,
        23935.42500,  177231.60000, 36827.02500,  30040.65000,   43931.25000,
        16331.70000,  21992.60000,  46032.00000,  1052973.60000, 16956.87500,
        17073.90000,  290926.75000, 156127.15000, 30385.50000,   26231.80000,
        95817.00000,  61825.95000,  5775.00000,   30675.00000,   93057.52500,
        34927.45000,  9046.50000,   2603.12500,   114118.80000,  10694.85000},
       {8845.77500,   5984.51250,   66066.00000,  142841.73750,  2040.18750,
        52622.86250,  266358.37500, 108940.83750, 1977.11250,    1986.00000,
        477721.56250, 84557.90000,  139911.37500, 14963.16250,   48346.68750,
        36497.85000,  17709.92500,  282712.30000, 22071.08750,   12180.18750,
        3108.87500,   67091.96250,  50189.21250,  31946.60000,   64804.57500,
        33148.16250,  183947.40000, 53033.51250,  42325.62500,   56547.56250,
        21757.31250,  30199.57500,  62514.81250,  1415639.40000, 24582.18750,
        27353.92500,  394035.96250, 218284.78750, 34060.31250,   35444.50000,
        143032.08750, 93199.68750,  13994.06250,  38943.75000,   68042.36250,
        38748.21250,  12767.77500,  2678.46250,   155275.50000,  17196.67500},
       {11656.27500,  6919.76250,   66973.20000,  137025.78750,  1600.76250,
        53852.66250,  256048.87500, 104203.68750, 1509.33750,    2088.40000,
        453818.31250, 81009.70000,  133534.27500, 15041.81250,   54681.18750,
        38302.65000,  17551.72500,  269592.70000, 18497.46250,   16314.18750,
        2532.22500,   77038.23750,  48040.31250,  32615.40000,   63420.77500,
        32667.93750,  276549.00000, 52629.61250,  43386.02500,   57636.56250,
        23235.71250,  29780.97500,  69570.31250,  1359472.20000, 28075.93750,
        27097.72500,  378067.11250, 208713.56250, 23696.81250,   34157.10000,
        141855.38750, 81191.93750,  15320.93750,  47856.25000,   115551.56250,
        21302.81250,  8172.37500,   3717.26250,   148907.10000,  18323.32500},
       {8663.27500,   4385.88750,   16203.60000, 12183.41250,  1836.36250,
        15197.81250,  46244.62500,  20704.61250, 2144.58750,   1668.40000,
        149807.43750, 19673.30000,  27615.77500, 2868.93750,   26698.68750,
        29842.65000,  8184.02500,   69254.90000, 9863.83750,   11614.68750,
        1643.02500,   36405.78750,  13492.61250, 8227.00000,   30250.27500,
        7022.23750,   352989.00000, 14201.41250, 15128.77500,  17925.18750,
        7608.56250,   8448.47500,   24685.68750, 178024.20000, 14222.81250,
        14443.27500,  42170.61250,  34439.81250, 59070.18750,  3636.70000,
        50787.21250,  41538.43750,  17905.93750, 25093.75000,  187935.86250,
        59235.56250,  16219.87500,  3300.76250,  11949.90000,  9376.72500}};

   constexpr int nvars = num_facilities * num_customers + num_facilities;
   constexpr int nrows = num_facilities + num_customers;

   unsigned char integral[nvars];
   double lbs[nvars];
   double ubs[nvars];
   double obj[nvars];
   double rowsides[nrows];
   unsigned char rowtypes[nrows];

   std::vector<std::string> names;
   names.reserve( nvars + num_customers + num_facilities );
   const char* colnames[nvars];
   const char* rownames[num_customers + num_facilities];

   // all vars binary
   int nassignvars = nvars - num_facilities;

   int i = 0;
   for( ; i != nassignvars; ++i )
   {
      integral[i] = 1;
      lbs[i] = 0;
      ubs[i] = 1;

      int f = i / num_customers;
      int c = i - num_customers * f;
      obj[i] = facility_customer_service_cost[f][c];
      names.emplace_back( fmt::format( "x#{}#{}", f + 1, c + 1 ) );
      colnames[i] = names.back().c_str();
   }

   for( ; i != nvars; ++i )
   {
      integral[i] = 1;
      lbs[i] = 0;
      ubs[i] = 1;

      int f = i - nassignvars;
      assert( 0 <= f && f < num_facilities );
      obj[i] = facility_fixcost[f];
      names.emplace_back( fmt::format( "y#{}", f + 1 ) );
      colnames[i] = names.back().c_str();
   }

   for( i = 0; i != num_customers; ++i )
   {
      rowtypes[i] = PAPILO_ROW_TYPE_EQUAL;
      rowsides[i] = 1;
      names.emplace_back( fmt::format( "assign_{}", i + 1 ) );
      rownames[i] = names.back().c_str();
   }

   for( ; i != nrows; ++i )
   {
      rowtypes[i] = PAPILO_ROW_TYPE_LESSER;
      rowsides[i] = 0;
      names.emplace_back( fmt::format( "capac_{}", i - num_customers + 1 ) );
      rownames[i] = names.back().c_str();
   }

   PAPILO_PROBLEM* prob = papilo_problem_create(
       1e30, "sscflp_cap101",
       num_facilities + 2 * num_customers * num_facilities, nrows, nvars );

   papilo_problem_add_cols( prob, nvars, lbs, ubs, integral, obj, colnames );

   papilo_problem_add_simple_rows( prob, nrows, rowtypes, rowsides, rownames );

   double assign_nonzeros[num_facilities];
   for( i = 0; i != num_facilities; ++i )
      assign_nonzeros[i] = 1.0;

   int assign_nonzero_inds[num_facilities];
   for( i = 0; i != num_customers; ++i )
   {
      for( int j = 0; j != num_facilities; ++j )
         assign_nonzero_inds[j] = i + j * num_customers;

      papilo_problem_add_nonzeros_row( prob, i, num_facilities,
                                       assign_nonzero_inds, assign_nonzeros );
   }

   int capacity_nonzero_inds[num_customers + 1];
   for( ; i != nrows; ++i )
   {
      int f = i - num_customers;
      for( int j = 0; j != num_customers; ++j )
         capacity_nonzero_inds[j] = j + f * num_customers;

      capacity_nonzero_inds[num_customers] = nassignvars + f;

      papilo_problem_add_nonzeros_row( prob, i, num_customers,
                                       capacity_nonzero_inds, customer_demand );
      papilo_problem_add_nonzero( prob, i, nassignvars + f,
                                  -facility_capacity[f] );
   }

   PAPILO_SOLVER* solver = papilo_solver_create();
   papilo_solver_load_problem( solver, prob );
   papilo_problem_free( prob );

   PAPILO_PARAM_RESULT paramRes =
       papilo_solver_set_param_real( solver, "message.verbosity", 4 );
   REQUIRE( paramRes == PAPILO_PARAM_WRONG_TYPE );

   paramRes = papilo_solver_set_param_int( solver, "message.verbosity", 5 );
   REQUIRE( paramRes == PAPILO_PARAM_INVALID_VALUE );

   paramRes = papilo_solver_set_param_int( solver, "message.verbosity", 4 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );

   paramRes =
       papilo_solver_set_mip_param_int( solver, "presolving/maxrounds", 0 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );

   paramRes = papilo_solver_set_mip_param_int64(
       solver, "heuristics/dins/nwaitingnodes", 20 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );

   paramRes = papilo_solver_set_mip_param_bool( solver, "lp/presolving", 0 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );

   paramRes = papilo_solver_set_param_real( solver, "presolve.tlimsoft", 10.0 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );

   paramRes =
       papilo_solver_set_lp_param_int( solver, "factor_update_max", 500 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );
   paramRes = papilo_solver_set_lp_param_int( solver, "displayfreq", 10000 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );
   paramRes = papilo_solver_set_lp_param_int( solver, "simplifier", 0 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );
   paramRes = papilo_solver_set_lp_param_int( solver, "scaler", 6 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );
   paramRes = papilo_solver_set_lp_param_int( solver, "pricer", 3 );
   REQUIRE( paramRes == PAPILO_PARAM_CHANGED );

   // papilo_solver_set_num_threads(solver, 1);
   PAPILO_SOLVING_INFO* result = papilo_solver_start( solver );

   REQUIRE( result->solve_result == PAPILO_SOLVE_RESULT_OPTIMAL );
   REQUIRE( result->bestsol_obj == Approx( 796648.4375 ) );
   REQUIRE( result->dualbound == Approx( 796648.4375 ) );
   REQUIRE( result->bestsol_intviol >= 0.0 );
   REQUIRE( result->bestsol_boundviol >= 0.0 );
   REQUIRE( result->bestsol_consviol >= 0.0 );
   REQUIRE( result->bestsol_intviol <= 1e-9 );
   REQUIRE( result->bestsol_boundviol <= 1e-9 );
   REQUIRE( result->bestsol_consviol <= 1e-9 );

   const double* sol = result->bestsol;
   REQUIRE( sol != nullptr );

   double objval = 0;
   for( int i = 0; i != nvars; ++i )
      objval += obj[i] * sol[i];
   REQUIRE( objval == Approx( 796648.4375 ) );

   papilo_solver_free( solver );
}

TEST_CASE( "papilolib-no-rows", "[C-API]" )
{
   PAPILO_PROBLEM* prob =
       papilo_problem_create( 1e30, "no_constraints", 0, 0, 2 );

   double lbs[2];
   double ubs[2];
   double obj[2];
   unsigned char integral[2];
   lbs[0] = ubs[0] = obj[0] = 1;
   lbs[1] = ubs[1] = obj[1] = 1;
   integral[0] = 1;
   integral[1] = 1;
   papilo_problem_add_cols( prob, 2, lbs, ubs, integral, obj, NULL );

   PAPILO_SOLVER* solver = papilo_solver_create();
   papilo_solver_load_problem( solver, prob );
   papilo_problem_free( prob );

   PAPILO_SOLVING_INFO* result = papilo_solver_start( solver );

   REQUIRE( result->solve_result == PAPILO_SOLVE_RESULT_OPTIMAL );
   REQUIRE( result->dualbound == 2.0 );
   REQUIRE( result->bestsol_obj == 2.0 );
   REQUIRE( result->bestsol_intviol == 0.0 );
   REQUIRE( result->bestsol_consviol == 0.0 );
   REQUIRE( result->bestsol_boundviol == 0.0 );
   REQUIRE( result->bestsol != nullptr );
   REQUIRE( result->bestsol[0] == 1.0 );
   REQUIRE( result->bestsol[1] == 1.0 );

   papilo_solver_free( solver );
}