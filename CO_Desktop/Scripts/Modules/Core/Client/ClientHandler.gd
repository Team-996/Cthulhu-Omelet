extends Node2D

@onready var sprite2D: Sprite2D = $Sprite2D
@onready var animation_player: AnimationPlayer = $AnimationPlayer

var window_width
var window_height
var window_size
var window_position

func _ready() -> void:
	window_width = ProjectSettings.get_setting("display/window/size/viewport_width")
	window_height = ProjectSettings.get_setting("display/window/size/viewport_height")
	window_size = Vector2i(window_width,window_height)
	 # 获取当前屏幕的分辨率和偏移量
	var screen_index = DisplayServer.window_get_current_screen()
	var screen_size = DisplayServer.screen_get_size(screen_index)
	var screen_position = DisplayServer.screen_get_position(screen_index) # 当前屏幕在多显示器中的起始坐标
	# 计算窗口在屏幕右下角的全局位置
	window_position = screen_position + screen_size - window_size
	DisplayServer.window_set_position(window_position)
	print("Screen Size:", screen_size)
	print("Window Size:", window_size)
	print("Window Position:", window_position)
	
	
func _input(event: InputEvent) -> void:
	if event.is_action_pressed("quit_game"):
		get_tree().quit()
	if event is InputEventMouseButton and event.button_mask == MOUSE_BUTTON_MASK_RIGHT:
		var local_mouse_pos = DisplayServer.mouse_get_position()
		if sprite2D.is_mouse_over_sprite(local_mouse_pos, window_position+window_size/2):	
			printt(local_mouse_pos)
			print(get_viewport().get_mouse_position())
		else:
			#animation_player.play("Run_L")
			print("Mouse is not over the sprite!") 
