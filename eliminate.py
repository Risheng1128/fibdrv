import subprocess
import numpy as np

def process(datas, samples, threshold = 2):
    datas = np.array(datas)
    res = np.zeros((samples, 3))
    
    mean = [datas[:,0].mean(), datas[:,1].mean(), datas[:,2].mean()]
    std = [datas[:,0].std(), datas[:,1].std(), datas[:,2].std()]
    cnt = 0 # 計算有幾組資料被捨去
    for i in range(samples):
        for j in range(runs):
            tmp = np.abs((datas[j * samples + i] - mean) / std)
            if tmp[0] > threshold or tmp[1] > threshold or tmp[2] > threshold: # 有一個資料過大，整組捨去
                cnt += 1
                datas[j * samples + i] = [0, 0, 0]
            res[i] += datas[j * samples + i]
        res[i] /= (runs - cnt)
        cnt = 0
    return res

if __name__ == '__main__':
    runs = 50   # 執行次數
    samples = 100 # 一次有幾個點
    datas = []

    for i in range(runs):
        subprocess.run('sudo taskset 0x1 ./client > out', shell = True)
        fr = open('out', 'r')
        for line in fr.readlines():
            datas.append(line.split(' ', 2))
        fr.close()
    
    datas = np.array(datas).astype(np.double)
    np.savetxt('final', process(datas, samples))
