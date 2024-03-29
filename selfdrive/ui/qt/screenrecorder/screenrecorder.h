#pragma once

#include <QPushButton>

#include "omx_encoder.h"
#include "blocking_queue.h"
#include "selfdrive/ui/ui.h"

class ScreenRecorder : public QPushButton {
#ifdef WSL2
  public:
    explicit ScreenRecorder(QWidget *parent = nullptr){}
    ~ScreenRecorder() override{}
    void update_screen(){}
    void toggle(){}
#else
  Q_OBJECT

public:
  explicit ScreenRecorder(QWidget *parent = nullptr);
  ~ScreenRecorder() override;
  void update_screen();
  void toggle();

public slots:
  void buttonPressed();
  void buttonReleased();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  BlockingQueue<QImage> image_queue;
  QColor recording_color;
  QWidget *rootWidget;
  bool recording = false;
  int frame = 0;
  int recording_width, recording_height;
  int screen_width = 2160, screen_height = 1080;
  long long started = 0;
  std::unique_ptr<OmxEncoder> encoder;
  std::unique_ptr<uint8_t[]> rgb_scale_buffer;
  std::thread encoding_thread;

  void applyColor();
  void closeEncoder();
  void encoding_thread_func();
  void initializeEncoder();
  void openEncoder(const char *filename);
  void start();
  void stop();
#endif //WSL2
};
