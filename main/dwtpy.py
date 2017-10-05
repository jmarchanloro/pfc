import pywt
from numpy import loadtxt

def doDWT(signal, f, l):
  #signal = loadtxt('Z001.txt')
  coeffs = pywt.wavedec(signal, f, level=l)
  cA_5, cD_5, cD_4, cD_3, cD_2, cD_1 = coeffs

  #print cA_5

  return [cA_5, cD_5, cD_4, cD_3, cD_2, cD_1]
#if __name__ == '__main__':
#  doDWT()
  #mismoS valores que en matlab (getCoefficients.m)

