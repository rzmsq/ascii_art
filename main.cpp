#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("/home/rzms/CLionProjects/ascii_art/images.bmp", std::ios::binary);

    if (!input.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    int offset;
    input.seekg(10);
    input.read(reinterpret_cast<char*>(&offset), 4);
    std::cout << offset << std::endl;

    int width;
    input.seekg(18);
    input.read(reinterpret_cast<char*>(&width), 4);
    std::cout << width << std::endl;

    int height;
    input.seekg(22);
    input.read(reinterpret_cast<char*>(&height), 4);
    std::cout << height << std::endl;

    int biteByPixel;
    input.seekg(28);
    input.read(reinterpret_cast<char*>(&biteByPixel), 2);
    std::cout << biteByPixel << std::endl;

    biteByPixel /= 8;

    // start
    input.seekg(offset);

    // array of bites img
    const auto buffer = new char[width * height * biteByPixel];
    for (int i = 0; i < height; i++) {
        input.read(buffer + i * width * biteByPixel, width * biteByPixel);
    }

    const double scale_x = static_cast<double>(width) / 180;
    const double scale_y = static_cast<double>(height) / 80;

    // array of brightness
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Определяем диапазон пикселей для текущего символа
            int start_x = static_cast<int>(j * scale_x);
            int end_x = static_cast<int>((j + 1) * scale_x);
            int start_y = static_cast<int>(i * scale_y);
            int end_y = static_cast<int>((i + 1) * scale_y);

            // Вычисляем среднюю яркость блока
            double sum_brightness = 0.0;
            int count = 0;
            for (int py = start_y; py < end_y && py < height; py++) {
                for (int px = start_x; px < end_x && px < width; px++) {
                    int index = (height - 1 - py) * width * biteByPixel + px * biteByPixel;
                    unsigned char B = buffer[index];
                    unsigned char G = buffer[index + 1];
                    unsigned char R = buffer[index + 2];
                    double brightness = 0.299 * R + 0.587 * G + 0.114 * B;
                    sum_brightness += brightness;
                    count++;
                }
            }
            double brightness = (count > 0) ? sum_brightness / count : 0.0;

            if (brightness >= 0.0 && brightness < 25.0) {
                std::cout << ' ';
            }
            if (brightness >= 25.0 && brightness < 51.0) {
                std::cout << '.';
            }
            if (brightness >= 50.0 && brightness < 76.0) {
                std::cout << ':';
            }
            if (brightness >= 76.0 && brightness < 101.0) {
                std::cout << '-';
            }
            if (brightness >= 101.0 && brightness < 127.0) {
                std::cout << '=';
            }
            if (brightness >= 127.0 && brightness < 152.0) {
                std::cout << '+';
            }
            if (brightness >= 152.0 && brightness < 177.0) {
                std::cout << '*';
            }
            if (brightness >= 177.0 && brightness < 202.0) {
                std::cout << '#';
            }
            if (brightness >= 202.0 && brightness < 227.0) {
                std::cout << '%';
            }
            if (brightness >= 227.0 && brightness < 256.0) {
                std::cout << '@';
            }
        }
        std::cout << std::endl;
    }

    delete[] buffer;
    input.close();
    return 0;
}