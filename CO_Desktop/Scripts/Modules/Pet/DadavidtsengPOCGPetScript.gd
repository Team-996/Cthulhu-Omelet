extends Sprite2D

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
	
