import seat_booking

aircraft=seat_booking.Aircraft(1,2,3,7,8,13,6)

while True:
  aircraft.show()
  print "# insert row and seat number, space-separated (empty line to quit)",
  try:
    input=raw_input()
  except EOFError: # ctrl-D is allowed
    print
    break
  if len(input)<1: break
  try:
    (row,seat)=map(lambda x: int(x),input.split())
    aircraft.seat_occupy(row,seat)
  except:
    pass
