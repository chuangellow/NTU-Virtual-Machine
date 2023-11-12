import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 1126)
client_socket.connect(server_address)

try:
    data = client_socket.recv(1024)
    message = str(data, encoding='utf-8')
    print(f'received the following message:\n{message}')
    with open('/r11944040_clientvol/received.txt', 'w') as f:
        f.write(message)
    if message == 'R11944040 sending from the server':
        print('Terminating client...')
finally:
    print('closing socket')
    client_socket.close()
