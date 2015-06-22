#!/usr/bin/env python
# -*- coding: utf-8 -*-

import subprocess as sp
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import numpy as np

def main():
    instance = "instancias/informatica/bacp12.txt"
    m_iter   = '200'
    alpha    = '0.9'
    t_init   = '1.0'
    t_eps    = '0.00001'
    x        = range(25,500,50)
    reps     = 50.0

    iters = dict()
    for j in x:
        total_time     = 0.0
        total_credits  = 0
        total_costs    = 0
        total_corrects = 0
        for i in range(int(reps)):
            sa = sp.Popen(['./bacp', '-d', '-f', instance, '-i', str(j), '-a', alpha, '-T', t_init, '-t', t_eps], stdout=sp.PIPE )
            output         = sa.communicate()[0].split()
            optimum        = int(output[3])
            total_credits  += int(output[0])
            total_costs    += int(output[1])
            total_time     += float(output[2])
            total_corrects += 1 if int(output[1]) == optimum else 0
        iters[j] = [total_credits/reps, total_costs/reps, total_time/reps, total_corrects/reps]
    print iters

    # x = range(100,1100,100)
    # iters = {800: [17.0, 17.0, 1.3997711200000003, 1.0], 100: [17.0, 17.0, 0.17331092999999995, 1.0], 200: [17.0, 17.0, 0.34634371000000014, 1.0], 300: [17.0, 17.0, 0.5185156500000001, 1.0], 400: [17.0, 17.0, 0.6976072099999999, 1.0], 1000: [17.0, 17.0, 1.7722891999999997, 1.0], 500: [17.0, 17.0, 0.8790793500000004, 1.0], 600: [17.0, 17.0, 1.0551463099999998, 1.0], 900: [17.0, 17.0, 1.5798861800000004, 1.0], 700: [17.0, 17.0, 1.2306101199999997, 1.0]}

    # x = range(25, 250, 25)
    # iters = {225: [17.0, 17.0, 0.39511328, 1.0], 100: [17.0, 17.0, 0.17340198000000004, 1.0], 200: [17.0, 17.0, 0.35464396, 1.0], 75: [17.0, 17.0, 0.15048686000000003, 1.0], 175: [17.0, 17.0, 0.32162786000000004, 1.0], 50: [17.2, 17.2, 0.09464729999999999, 0.8], 150: [17.0, 17.0, 0.26840738000000003, 1.0], 125: [17.0, 17.0, 0.22266102000000007, 1.0]}

    # x = range(250, 425, 25)
    # iters = 325: [14.0, 14.0, 0.5632130000000001, 1.0], 300: [14.04, 14.04, 0.5038292200000001, 0.96], 400: [14.02, 14.02, 0.6430246199999999, 0.98], 275: [14.0, 14.0, 0.4611342, 1.0], 375: [14.0, 14.0, 0.6070340799999999, 1.0], 250: [14.0, 14.0, 0.42622106000000004, 1.0], 350: [14.0, 14.0, 0.5606740799999997, 1.0]}

    # x = range(325, 525, 25)
    # iters = {450: [14.0, 14.0, 0.8262815799999998, 1.0], 325: [14.0, 14.0, 0.5266921399999999, 1.0], 425: [14.02, 14.02, 0.7428214000000001, 0.98], 400: [14.04, 14.04, 0.68571152, 0.96], 500: [14.0, 14.0, 0.82300424, 1.0], 375: [14.0, 14.0, 0.6398409999999997, 1.0], 475: [14.0, 14.0, 0.8110658600000002, 1.0], 350: [14.04, 14.04, 0.6322237000000002, 0.96]}

    # x        = range(25,500,50)
    # iters = {225: [18.0, 18.0, 0.8597139000000003, 1.0], 325: [18.0, 18.0, 1.1879471399999997, 1.0], 425: [17.98, 17.98, 1.5452704400000001, 0.98], 75: [18.12, 18.12, 0.28541778000000007, 0.88], 175: [18.0, 18.0, 0.63177236, 1.0], 275: [18.0, 18.0, 1.02299514, 1.0], 375: [18.0, 18.0, 1.3745446400000003, 1.0], 25: [18.34, 18.34, 0.09284868000000002, 0.66], 475: [18.0, 18.0, 1.7391491, 1.0], 125: [18.02, 18.02, 0.46624435999999997, 0.98]}

    reps     = 50.0
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
