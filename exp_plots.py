import pandas as pd
import matplotlib.pyplot as plt

bi_gcc_df = pd.read_csv("bi_gcc_mr.csv")
bi_jpeg_df = pd.read_csv("bi_jpeg_mr.csv")
# print(df)

# bi_gcc
plt.plot(bi_gcc_df['m'], bi_gcc_df['rate'])
plt.xlabel("m values")
plt.ylabel("missprediction rate")
plt.title("bimodal gcc misprediction rates")
plt.legend()
plt.show()

# bi_jpeg
plt.plot(bi_jpeg_df['m'], bi_jpeg_df['rate'])
plt.xlabel("m values")
plt.ylabel("missprediction rate")
plt.title("bimodal jpeg misprediction rates")
plt.legend()
plt.show()