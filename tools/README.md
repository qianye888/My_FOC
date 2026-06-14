# FOC log viewer

固件串口会输出 CSV 日志，默认 50 ms 一行：

```csv
time_ms,angle_cmd,angle_fb,speed_cmd,speed_fb,uq_cmd,ud_cmd,pwm_amp,cmp_a,cmp_b,cmp_c
```

使用方法：

1. 用串口工具连接 USART2，波特率保持工程里的 `19200`。
2. 保存串口输出为 `.csv`、`.log` 或 `.txt` 文件。
3. 用浏览器打开 `tools/log_viewer.html`。
4. 选择保存的日志文件，即可查看角度、速度和 PWM 波形。

字段说明：

- `angle_cmd` / `angle_fb`: 角度指令和角度反馈。
- `speed_cmd` / `speed_fb`: 速度指令和速度反馈。
- `uq_cmd` / `ud_cmd`: FOC d/q 轴电压指令。
- `pwm_amp`: 输出电压矢量幅值。
- `cmp_a` / `cmp_b` / `cmp_c`: 下发到 TIM1 的三相 PWM 比较值。

采样间隔由 `FOC/FOC_Log.h` 里的 `FOC_LOG_DEFAULT_DIVIDER` 控制。当前控制周期是 10 ms，分频为 5 时日志周期是 50 ms；如果要记录 10 ms 细节，建议同时把串口波特率提高到 115200。
