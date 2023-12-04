sub test1
0:
    pos = [480,-16]
    angle = 90
    speed = 2
    agl_spd = 0
30:
    agl_spd = -3
60:
    agl_spd = 0
    angle = 0
90:
    agl_spd = 3
120:
    agl_spd = 0
    angle = 90
end sub

sub test2
0:
    pos = [640,-16]
    angle = 90
    speed = 4
    accel = -0.066667
    agl_spd = 0
30:
    agl_spd = -3
    accel = 0
    speed = 2
60:
    agl_spd = 0
    angle = 0
120:
    agl_spd = 3
150:
    agl_spd = 0
    angle = 90
    accel = 0.066667
180:
	speed = 4
    accel = 0

200:
    accel = -0.1

230:
	accel = 0
	speed = 1
end sub