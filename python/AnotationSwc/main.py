import swc
import os
import cv2 as cv
import multiprocessing as mpg
import numpy as np


def pro100(cp, s_z, t, p):
    try:
#         print cp, os.getpid()
        green_src = r'Z:\AppData\TDI\part3\TDI11302020\green\montage'
        red_src = r'W:\lsu\TDI11302020\red\montage'
        res = (0.3, 0.3, 1)    
        m_z = int(cp[2]) + s_z
        m_x = int(cp[0])
        m_y = int(cp[1])
        s_z = m_z - t / 2;
        e_z = m_z + t / 2 - 1;
        pre = 'test_'
        suf = '_mon.tif'
        dst = r'W:\lsu\TDI11302020\all\cells'
        r = 10
        ball_r = ball(r)
        res_shape = [0, 0]
        for i in xrange(s_z, e_z, 1):
            green_name = green_src + '\\' + pre + '%05d'%(i) + suf
            red_name = red_src + '\\' + pre + '%05d'%(i) + suf
            print red_name
            green_im = cv.imread(green_name, cv.CV_LOAD_IMAGE_UNCHANGED)
            red_im = cv.imread(red_name, cv.CV_LOAD_IMAGE_UNCHANGED)
            if i == s_z:
                raw_shape = red_im.shape
                res_shape = (int(raw_shape[1] * 0.3), int(raw_shape[0] * 0.3))
                out_green = np.zeros((int(raw_shape[0] * 0.3), int(raw_shape[1] * 0.3)), dtype=np.uint16)
                out_red = np.zeros((int(raw_shape[0] * 0.3), int(raw_shape[1] * 0.3)), dtype=np.uint8)
            green_im = cv.resize(green_im, res_shape)
            red_im = cv.resize(red_im, res_shape)
            out_green = np.maximum(out_green, green_im)
            out_red = np.maximum(out_red, red_im)
        out_red = cv.cvtColor(out_red, cv.cv.CV_GRAY2RGB)                        #out_red¡®shape is [y, x, 3] rather than [3, y, x]    
        for i in xrange(len(ball_r)):
            for j in xrange(len(ball_r)):
                if ball_r[i][j] == 1:
                    out_green[m_y + i - r, m_x + j - r] = 0;
                    out_red[m_y + i - r, m_x + j - r, 0] = 0;
                    out_red[m_y + i - r, m_x + j - r, 1] = 255;
                    out_red[m_y + i - r, m_x + j - r, 2] = 0;
        cv.imwrite(dst+'\\g_' + p + '_p.tif', out_green)
        cv.imwrite(dst+'\\r_' + p + '_p.tif', out_red)
            
            
            
            
    except Exception, e:
        print Exception, e
    


def ball(r):
    ball_list = []
    for i in xrange(2 * r + 1):
        ball_list.append([0] * (2 * r + 1))
    for i in xrange(2 * r + 1):
        for j in xrange(2 * r + 1):
            if ((i - r) ** 2 + (j -  r) ** 2) <= r ** 2:
                ball_list[i][j] = 1
    return ball_list
    



if __name__ == '__main__':
    srcs = dict()
    srcs['sl'] = r'W:\lsu\TDI11302020\all\sl\den'
    srcs['jy'] = r'W:\lsu\TDI11302020\all\jy\tmp'
    srcs['zhm'] = r'W:\lsu\TDI11302020\all\zhm2.22\den'
    srcs['lyr'] = r'W:\lsu\TDI11302020\all\lyr\den'
    shift_z = 28
    block = 100
    pro_pool = mpg.Pool(processes=4)
    
    for i in srcs:
        t_swc_src = srcs[i]
        t_swc_name = os.listdir(t_swc_src)[0]
        t_swc_path = t_swc_src + '\\' + t_swc_name
        t_swc = swc.Swc(t_swc_path, (0.3, 0.3, 1))
        cell_point = t_swc.node_list[0][2 : 5]
        pro_pool.apply_async(func=pro100, args=(cell_point, shift_z, block, i))
    pro_pool.close()
    pro_pool.join()
    ball(1)
    print "all done!"