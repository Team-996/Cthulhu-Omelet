extends Node2D

@onready var pet_sprite: PetSprite = $pet_sprite
#@onready var pet_anim: AnimationPlayer = $pet_anim
@onready var button_anim: AnimationPlayer = $button_anim
@onready var button: Button = $Button



var window_width
var window_height
var window_size
var window_position


func _ready() -> void:
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
	print("Screen Size:", screen_size)
	print("Window Size:", window_size)
	print("Window Position:", window_position)


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("quit_game"):
		get_tree().quit()
	if event is InputEventMouseButton and event.button_mask == MOUSE_BUTTON_MASK_RIGHT:
		var screen_mouse_pos: Vector2i = DisplayServer.mouse_get_position()
		if pet_sprite.is_mouse_over_sprite(screen_mouse_pos, window_position+window_size/2):
			print("MOUSE SCREEN POS: ", screen_mouse_pos)
			print("Mouse is hovering over the visible part of the sprite!")
		else:
			print("Mouse is not over the sprite!")

	# TODO: pixel perfect detection when animation player is playing
	if event.is_action_pressed("pet_start_running"):
		#pet_anim.play("Run_L")
		button_anim.play("button_move")
		
	#if event.is_action_pressed("pet_stop_running"):
		#pet_anim.pause()
