#!/usr/bin/env python
# -*- coding: utf-8 -*-

import subprocess as sp
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import numpy as np

def main():
    instance = "instancias/informatica/bacp8.txt"
    m_iter   = '200'
    alpha    = '0.9'
    t_init   = '1.0'
    t_eps    = '0.00001'
    optimum  = 17
    x        = range(100,1100,100)
    reps     = 100.0

    # iters = dict()
    # for j in x:
    #     total_time     = 0.0
    #     total_credits  = 0
    #     total_costs    = 0
    #     total_corrects = 0
    #     for i in range(int(reps)):
    #         sa = sp.Popen(['./bacp', '-d', '-f', instance, '-i', str(j), '-a', alpha, '-T', t_init, '-t', t_eps], stdout=sp.PIPE )
    #         output         = sa.communicate()[0].split()
    #         total_credits  += int(output[0])
    #         total_costs    += int(output[1])
    #         total_time     += float(output[2])
    #         total_corrects += 1 if int(output[1]) == optimum else 0
    #     iters[j] = [total_credits/reps, total_costs/reps, total_time/reps, total_corrects/reps]
    # print iters

    #iters = {800: [17.08, 17.38, 0.79920246], 100: [17.32, 18.92, 0.10429536], 200: [17.0, 18.46, 0.2118326], 300: [17.08, 17.62, 0.32225456], 400: [17.0, 17.52, 0.41700658], 1000: [17.0, 17.54, 1.0040644], 500: [17.0, 17.9, 0.5400428000000002], 600: [17.08, 17.78, 0.6229977199999999], 900: [17.02, 17.42, 0.9002242199999999], 700: [17.0, 17.54, 0.7104738399999999]}
    #iters = {200: [17.0, 18.46, 0.20341994, 0.1], 300: [17.0, 17.74, 0.30310078000000007, 0.32], 400: [17.06, 17.78, 0.4130137999999999, 0.38], 100: [17.0, 18.26, 0.10196160000000004, 0.18]}

    #bacp8 : x = range(100, 1100, 100)
    iters = {800: [17.0, 17.0, 0.82714016, 1.0], 100: [17.09, 135.09, 0.10703691999999995, 0.58], 200: [17.0, 69.0, 0.21666104000000005, 0.79], 300: [17.02, 53.02, 0.31969196, 0.83], 400: [17.03, 47.03, 0.41135266000000015, 0.82], 1000: [17.0, 17.0, 1.0318877, 1.0], 500: [17.0, 49.0, 0.5143889199999999, 0.84], 600: [17.0, 23.0, 0.6590330099999997, 0.97], 900: [17.0, 19.0, 0.9282144099999996, 0.99], 700: [17.0, 29.0, 0.7574141299999998, 0.94]}

    #bacp10 : x = range(100,1100,100)
    #iters = {800: [14.02, 14.46, 0.7512205600000001, 0.6], 100: [14.66, 16.46, 0.09470606000000002, 0.0], 200: [14.0, 15.54, 0.18929107999999994, 0.36], 300: [14.0, 15.16, 0.28294094000000003, 0.38], 400: [14.0, 15.24, 0.37839523999999997, 0.28], 1000: [14.0, 14.44, 0.94209328, 0.68], 500: [14.04, 14.98, 0.47164112, 0.38], 600: [14.0, 14.74, 0.5657686599999999, 0.44], 900: [14.0, 14.56, 0.8468755400000001, 0.56], 700: [14.0, 14.36, 0.66017914, 0.82]}

    #bacp12 : x = range(100, 1100, 100)
    #iters = {800: [18.0, 18.0, 1.60388014, 1.0], 100: [18.1, 19.16, 0.19743009999999991, 0.54], 200: [18.06, 18.32, 0.39520967999999995, 0.8], 300: [18.0, 18.34, 0.62744136, 0.86], 400: [18.0, 18.12, 0.8194248600000001, 0.96], 1000: [18.0, 18.0, 2.0120225, 1.0], 500: [18.0, 18.02, 1.03043692, 0.98], 600: [18.0, 18.0, 1.22661958, 1.0], 900: [18.0, 18.06, 1.8095462, 0.98], 700: [18.0, 18.0, 1.4300231599999995, 1.0]}


    x_interp   = np.linspace(min(x), max(x), 50)
    y_credits  = map(lambda i: iters[i][0], x)
    y_costs    = map(lambda i: iters[i][1], x)
    y_time     = map(lambda i: iters[i][2], x)
    y_accurecy = map(lambda i: iters[i][3], x)
    f_credits  = interp1d(x, y_credits, kind='cubic')
    f_costs    = interp1d(x, y_costs, kind='cubic')
    f_time     = interp1d(x, y_time, kind='cubic')
    f_accurecy = interp1d(x, y_accurecy, kind='cubic')

    fig, ax1 = plt.subplots()
    ax1.plot(x, y_credits, 'bo', x_interp, f_credits(x_interp), 'b-',
             x,y_costs, 'ro', x_interp, f_costs(x_interp), 'r-')
    ax1.set_xlabel('n iteraciones')
    ax1.set_ylabel('Creditos/costo', color="r")
    ax1.axis([min(x),max(x),min(y_credits + y_costs)-0.25, max(y_credits + y_costs)+0.25])
    for tl in ax1.get_yticklabels():
        tl.set_color('r')

    ax2 = ax1.twinx()
    #ax2.plot(x, y_time, 'g.', x_interp, f_time(x_interp), 'g-')
    #ax2.set_ylabel('Tiempo (s)')
    #for tl in ax2.get_yticklabels():
    #    tl.set_color('g')
    ax2.plot(x, y_accurecy, 'go', x_interp, f_accurecy(x_interp), 'g-')
    ax2.set_ylabel('Accurecy')
    ax2.axis([min(x),max(x),0,1])
    for tl in ax2.get_yticklabels():
        tl.set_color('g')
    #plt.plot(x,y_credits, 'bo', x,y_costs, 'r-')
    #plt.axis([min(n)-50,max(n)+50,min(y_credits + y_costs)-0.25,max(y_credits + y_costs)+0.25])
    plt.show()

if __name__ == "__main__":
    main()
