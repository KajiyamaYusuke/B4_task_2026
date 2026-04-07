import pandas as pd
import numpy as np

def compare_csv(file1, file2, tolerance=1e-6):
    try:
        df1 = pd.read_csv(file1, header=None)
        df2 = pd.read_csv(file2, header=None)

        # Check if the shapes are the same
        if df1.shape != df2.shape:
            print(f"Shapes are different: {df1.shape} vs {df2.shape}")
            return False

        # Compare the values with tolerance
        diff = np.abs(df1 - df2)
        if np.max(diff.values) <= tolerance:
            print("CORRECT!!")
            return True
        else:
            print("WRONG")
            return True

    except FileNotFoundError:
        print("One or both files not found.")
        return False
    except Exception as e:
        print(f"An error occurred: {e}")
        return False


# main分
if __name__ == "__main__":
    file1 = "output.csv"    #ここは変えない
    file2 = "output2.csv"   #これを任意のファイル名に変更
    if compare_csv(file1, file2):
        exit(0)
    else:
        exit(1)