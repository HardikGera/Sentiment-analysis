def decode(message_file):
  
  decoded_message = ""
  message_dict = {}

  # Read the message file
  try:
    with open(message_file, "r") as file:
      for line in file:
        number, word = line.strip().split(" ", 1)
        message_dict[int(number)] = word
  except FileNotFoundError:
    print(f"Error: File '{message_file}' not found.")
    return None

  # Build the pyramid structure and extract message words
  current_level = 1
  pyramid_level_size = 1
  while message_dict:
    for number in sorted(message_dict.keys()):
      if number <= pyramid_level_size:
        decoded_message += message_dict.pop(number) + " "
        pyramid_level_size += 1
      else:
        break
    current_level += 1

  return decoded_message.strip()


decoded_message = decode("coding_qual_input.txt") 
if decoded_message:
  print("Decoded message:", decoded_message)
else:
  print("Decoding failed.")
