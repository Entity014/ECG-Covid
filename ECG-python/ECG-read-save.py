import serial
import csv
import time
import matplotlib.pyplot as plt

ser = serial.Serial("/dev/ttyUSB0", 9600)

current_time = time.time()
formatted_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(current_time))
filename = f"data-{formatted_time}.csv"

with open(filename, "w", newline="") as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(["ECG", "Time"])

    fig, ax = plt.subplots()
    ax.set_xlabel("Time (seconds)")
    ax.set_ylabel("ECG (mV)")
    ax.set_ylim([0, 1024])
    (line,) = ax.plot([], [])

    xdata, ydata = [], []
    while True:
        if ser.in_waiting:
            data = ser.readline().decode("utf-8").rstrip()
            data = data.split(", ")
            if len(data) == 3:
                _, ecg, time = data
                csvwriter.writerow([ecg, time])
                xdata.append(float(time))
                ydata.append(float(ecg))
                line.set_data(xdata, ydata)
                ax.relim()
                ax.autoscale_view()
                fig.canvas.draw_idle()
                plt.pause(0.001)
                print(f"ECG: {ecg} mV, Time: {time} seconds")
