extends Node2D

var window_width
var window_height
var window_size
var window_position
# TODO: Consider move string path to a config script or project config
const CLIENT_EXE_PATH: String = "C:/Users/Shangqi Cai/Downloads/BetterDiscord-Windows.exe"
var client_process_id: int    = -1

# Create the process check timer to check client process id periotically
# The Process checker timer is not set to auto start, it was controlled by whether ot not
# succesful start or shutdown the client in order to save scanning tasklist
@onready var process_check_timer: Timer = Timer.new()


# Check whether client is alive or not
func is_process_alive(process_id: int) -> bool:
	var output: Array[Variant] = []
	var exit_code: int         = OS.execute("tasklist", [], output, true)
	if exit_code == 0:
		var output_str: String = "\n".join(output)
		return str(process_id) in output_str
	return false


func _ready() -> void:

	# Connect events with safty check
	if not ClientEvent.is_connected("request_client_startup_event", on_request_client_startup):
		ClientEvent.connect("request_client_startup_event", on_request_client_startup)
	if not ClientEvent.is_connected("request_client_shutdown_event", on_request_client_shutdown):
		ClientEvent.connect("request_client_shutdown_event", on_request_client_shutdown)

	window_width = ProjectSettings.get_setting("display/window/size/viewport_width")
	window_height = ProjectSettings.get_setting("display/window/size/viewport_height")
	window_size = Vector2i(window_width, window_height)
	# 获取当前屏幕的分辨率和偏移量
	var screen_index: int         = DisplayServer.window_get_current_screen()
	var screen_size: Vector2i     = DisplayServer.screen_get_size(screen_index)
	var screen_position: Vector2i = DisplayServer.screen_get_position(screen_index) # 当前屏幕在多显示器中的起始坐标
	# 计算窗口在屏幕右下角的全局位置
	window_position = screen_position + screen_size - window_size
	DisplayServer.window_set_position(window_position)
	print_debug("Screen Size:", screen_size)
	print_debug("Window Size:", window_size)
	print_debug("Window Position:", window_position)

	# Setup and start the timer
	process_check_timer.wait_time = 5.0
	process_check_timer.autostart = false
	process_check_timer.one_shot = false
	process_check_timer.timeout.connect(_on_process_check_timer_timeout)
	add_child(process_check_timer)


# Check the process is alive if the process is not alive emit client close event and
# reset the client process id to -1
func _on_process_check_timer_timeout():
	if client_process_id != -1 and not is_process_alive(client_process_id):
		client_process_id = -1
		ClientEvent.emit_signal("client_shutdown_event")
		print_debug("Client process is no longer alive.")


# Request client shut down, return whether or not it shutdown succesful
# If the client shutdown succesfully, "client_shutdown_event" would emmited
func on_request_client_shutdown()->bool:
	if client_process_id != -1 and not is_process_alive(client_process_id):
		OS.kill(client_process_id)
		ClientEvent.emit_signal("client_shutdown_event")
		client_process_id = -1
		process_check_timer.stop()    # stop the timer becasue we know that the client is succesful shutdown
		push_warning("Process terminated.")
		return true
	else:
		push_warning("Try to shutdown the client but the client process is not alive")
	return false


# Request client start up, return whether or not it start succesful
# If the client start up succesfully, "client_startup_event" would emmited
func on_request_client_startup()->bool:
	if client_process_id == -1 or not is_process_alive(client_process_id):
		client_process_id = open_client()
		if client_process_id >= 0:
			print_debug("Process started successfully with PID:", client_process_id)
			ClientEvent.emit_signal("client_startup_event")
			process_check_timer.start()        # start the timer becasue we need know whether or not the client process is alive
			return true
		else:
			push_error("Failed to start process.")
			return false
	else:
		push_error("Process is already running with PID:", client_process_id)
		return false


func _exit_tree():
	if client_process_id != -1 and is_process_alive(client_process_id):
		OS.kill(client_process_id)
		push_warning("Process terminated.")


# Open the client return the process id
func open_client()-> int:
	client_process_id = OS.create_process(CLIENT_EXE_PATH, [])
	return  client_process_id
