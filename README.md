# WarframeTradeCLI

A cli tool to query warframe.market

## Dependencies

| Area         | Library         | Platform | Notes                          |
| ------------ | --------------- | -------- | ------------------------------ |
| HTTP         | `cpr`           | ✅ All   | Simplifies GET requests        |
| JSON         | `nlohmann/json` | ✅ All   | Clean and modern JSON handling |
| OCR          | `Tesseract`     | ✅ All   | Best open OCR; needs training  |
|              |                 |          | data (~50MB)                   |
| GUI/Overlay  | `Qt 6`          | ✅ All   | Transparent overlays, image    |
|              |                 |          | capture, clean UI              |
| Build System | `CMake`         | ✅ All   | Portable, great Qt and         |
|              |                 |          | third party integration        |
