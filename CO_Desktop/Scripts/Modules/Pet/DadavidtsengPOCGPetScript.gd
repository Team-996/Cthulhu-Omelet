extends Sprite2D

class_name TestSprite

const UNREAL_EXE_PATH: String = "C:/Users/Yu-Wei Tseng/Downloads/BetterDiscord-Windows.exe"
var unreal_process_id: int = -1

func is_process_alive(process_id: int) -> bool:
	var output = []
	var exit_code = OS.execute("tasklist", [], output, true)
	if exit_code == 0:
		for line in output:
			if str(process_id) in line:
				return true
	return false

func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT and event.pressed:
			print("Sprite clicked!")
			open_client()

func open_client():
	if unreal_process_id == -1 or not is_process_alive(unreal_process_id):
		unreal_process_id = OS.create_process(UNREAL_EXE_PATH, [])
		if unreal_process_id >= 0:
			print("Process started successfully with PID:", unreal_process_id)
		else:
			print("Failed to start process.")
	else:
		print("Process is already running with PID:", unreal_process_id)

func _exit_tree():
	if unreal_process_id != -1 and is_process_alive(unreal_process_id):
		OS.kill(unreal_process_id)
		print("Process terminated.")
		
#func _process(delta: float) -> void:
	#var local_mouse_pos = DisplayServer.mouse_get_position()
	#
	#if is_mouse_over_sprite(local_mouse_pos):
		#print("Mouse is hovering over the visible part of the sprite!")
	#else:
		#print("Mouse is not over the sprite!") 
		
func is_mouse_over_sprite(local_pos: Vector2, window_center_pos: Vector2)->bool:
	if texture == null:
		#print("A", )
		return false
	
	#var screen_size = DisplayServer.screen_get_size()
	
	var texture_width = texture.get_width()
	var texture_height = texture.get_height()
	
	if local_pos.x < window_center_pos.x-texture_width/2.0 or local_pos.y <  window_center_pos.y-texture_height/2.0 or local_pos.x > window_center_pos.x+texture_width/2.0 or local_pos.y > window_center_pos.y+texture_height/2.0:
		print("B /",local_pos, window_center_pos)
		#print(texture.get_size())
		return false
		
	var image = texture.get_image()
	if image == null:
		#print("C")
		return false
	
	#local_pos.y = image.get_height()-local_pos.y
	var mouse_position = get_viewport().get_mouse_position()
	var pixel_color = image.get_pixelv(mouse_position)
	print("PIXEL COLOR A: ", pixel_color, " / PIXEL POS:", mouse_position)
	
	return pixel_color.a != 0
		
			
	
