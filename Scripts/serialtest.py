import serial
import time

uart_p = serial.Serial('/dev/ttyUSB0', baudrate=2400, timeout=1)  
time.sleep(2)  

data_to_send = """Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one. In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs," Rajan said in the note." Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently.\n"""

start_time = time.time()

bytes_sent = uart_p.write(data_to_send.encode()) 

uart_p.flush()  # Ensure all data is sent
print("Data sent. Waiting for acknowledgment...")

# Wait for acknowledgment
ack = uart_p.readline().decode().strip()

end_time = time.time()

print(f"Sent data: \n\n{(data_to_send)}\n")

uart_p.close()

time_taken = end_time - start_time  # In seconds
bits_sent = bytes_sent * 8          # Convert bytes to bits
speed_bps = bits_sent / time_taken  # Speed in bps
# Display results
print(f"Time taken: {time_taken:.2f} seconds")
print(f"Speed: {speed_bps:.2f} bps")


