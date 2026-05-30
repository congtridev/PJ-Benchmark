# Cấu trúc dữ liệu và giải thuật
## Học kỳ 2 năm học 2025-2026

### 1. Nhóm sinh viên thực hiện
* Võ Nguyễn Công Trí - 25120455
* Đỗ Duy Trường      - 25120459
* Trần Kiến Văn      - 25120468

### 2. Giai đoạn 1: Phân tích và tối ưu 3 bài toán benchmark

#### Bài toán 1: Integer Sort
Mục tiêu là sắp xếp mảng N số nguyên có dấu 32-bit ($N \le 10^5$) theo thứ tự không giảm.

Ban đầu, nhóm dùng Merge Sort. Để tránh chi phí cấp phát bộ nhớ động, dữ liệu được lưu trực tiếp trên mảng tĩnh `int a[MAXN]` và `tmp[MAXN]`. Kỹ thuật tráo đổi mảng nguồn và đích qua từng tầng đệ quy giúp loại bỏ thao tác copy thừa. Nhóm cũng ép xung luồng I/O bằng `ios::sync_with_stdio(false)` và `cin.tie(nullptr)`.

Mặc dù, Merge Sort có độ phức tạp $\mathcal{O}(N \log N)$. Giới hạn của bộ đệm I/O và chi phí duy trì hàng ngàn lời gọi đệ quy vẫn tạo ra độ trễ. Để ép thời gian chạy xuống mức tuyến tính, nhóm quyết định đổi sang LSD Radix Sort.

* **Xử lý số âm:** Chương trình tải toàn bộ đầu vào bằng một lệnh `cin.read`. Để chia xô chung cho cả số âm và số dương, chúng tôi dùng phép XOR bit dấu (`^ 0x80000000`) hất toàn bộ trục số sang vùng dương.
* **LSD Radix Sort cơ số 65536:** Hệ thống tách số 32-bit thành 2 phần 16-bit. Lần chia xô thứ hai (xử lý nửa cao) bắt buộc phải dùng một thuật toán sắp xếp ổn định (Stable Sort) để không làm xáo trộn trật tự của nửa thấp trước đó.
* **Đánh giá:** Thuật toán chạy trong $\mathcal{O}(N + K)$. Kích thước mảng đếm 256KB tràn L1 Cache gây ra hiện tượng Cache Miss, nhưng bù lại vòng lặp chỉ phải quét qua mảng đúng 2 lần. Điều này dư sức bù đắp lại độ trễ của bộ nhớ đệm.

#### Bài toán 2: strlexi
Sắp xếp N chuỗi ký tự in thường ($N \le 10^5$, chiều dài $10 \le L \le 100$) theo thứ tự từ điển.

Lần nộp đầu chạy `std::vector<std::string>` và QuickSort với phân vùng Lomuto. Cách này dễ sập xuống $\mathcal{O}(N^2 \cdot L)$ nếu test có nhiều chuỗi giống nhau, vì toán tử `<` của `std::string` sẽ quét lại từ đầu các tiền tố đã khớp. Việc `cin >>` liên tục cấp phát động cho hàng trăm ngàn chuỗi cũng làm chậm đi hiệu năng.

Để khắc phục, nhóm tự quản lý bộ nhớ và chuyển sang MSD Radix Sort:
* **Đọc I/O theo khối:** Chúng tôi để file vào một mảng ký tự `pool` liên tục qua `cin.read`, sau đó dùng mảng con trỏ `char* pt[MAXN]` trỏ vào từng chuỗi để tránh chi phí khởi tạo đối tượng.
* **MSD Radix Sort:** Các chuỗi được phân loại theo từng ký tự từ trái sang phải. Nhờ vậy thuật toán hoàn toàn bỏ qua việc kiểm tra lại các tiền tố đã giống nhau.
* **Fallback sang Insertion Sort:** Khi mảng con thu hẹp xuống còn $N \le 15$, đệ quy tự ngắt và chuyển sang Insertion Sort. Mức $N$ này đủ nhỏ để Insertion Sort chạy nhanh hơn việc hệ thống phải cấp phát mảng đếm mới của Radix Sort.

#### Bài toán 3: strlenlexi
Sắp xếp N chuỗi ($N \le 10^4$, $10 \le L \le 100$) ưu tiên chiều dài tăng dần, sau đó mới đến thứ tự từ điển.

Thông thường mọi người hay gọi QuickSort kèm hàm so sánh tùy chỉnh. Cách này tốn nhiều không gian và rất dễ suy biến nếu mảng bị đảo ngược độ dài. Do đó, nhóm quyết định tách riêng tiêu chí độ dài ra trước:
* **Index Sorting bằng Bucket Sort:** Chiều dài tối đa chỉ đến 100, nên chúng tôi thiết lập 101 xô (bucket). Thay vì copy cả chuỗi, chương trình chỉ đưa chỉ số của chuỗi đó vào xô tương ứng.
* **Merge Sort cục bộ:** Bên trong mỗi xô lúc này là các chuỗi đã dài bằng nhau. Nhóm chỉ cần áp Merge Sort để xếp thứ tự từ điển. Việc gọi chuỗi thông qua chỉ số sinh ra Cache Miss, nhưng $N$ nhỏ nên tổng thời gian xử lý vẫn rất an toàn.

### 3. Thiết kế chương trình sinh test case (test_gen.cpp)
File `test_gen.cpp` tạo ra các kịch bản xấu nhất (worst-case) để bắt lỗi luồng I/O, khả năng dự đoán rẽ nhánh (Branch Predictor) và quản lý bộ nhớ đệm của các bài nộp.

#### A. Nhóm số nguyên - int: Quy mô N = 100.000
* **Test 1 - Ngẫu nhiên phân phối đều:** Kiểm tra tính đúng đắn cơ bản.
* **Test 2 - Đã sắp xếp tăng dần:** Đánh vào các bài nộp dùng QuickSort thuần chọn pivot kém, đồng thời kiểm chứng tính ổn định của Radix Sort.
* **Test 3 - Sắp xếp giảm dần:** Ép các thuật toán có độ phức tạp $\mathcal{O}(N^2)$ thực hiện số lần hoán đổi nhiều nhất.
* **Test 4 - Giá trị cực trị:** Nhồi các giá trị như `INT_MIN` và `INT_MAX` để test xem phép toán biến đổi bit dấu XOR có bị tràn số hay không.
* **Test 5 - Trùng lặp hoàn toàn:** Kiểm tra cách thuật toán cập nhật các mảng đếm tần suất.

#### B. Nhóm chuỗi - strlexi: Quy mô N = 100.000
* **Test 1 - Ký tự ngẫu nhiên:** Phân phối đều từ 'a' đến 'z'.
* **Test 2 - Chiều dài tối đa:** Toàn bộ chuỗi dài 98 ký tự. Test này sẽ làm cạn RAM hoặc gây Time Limit Exceeded (TLE) nếu bài nộp copy chuỗi theo tham trị.
* **Test 3 - Tiền tố chung dài:** Các chuỗi giống y hệt nhau ở 88 ký tự đầu, chỉ chệch vài ký tự đuôi. Thuật toán so sánh `<` truyền thống sẽ phải quét đi quét lại phần đầu, trong khi MSD Radix Sort thì lướt qua luôn.
* **Test 4 - Đã sắp xếp sẵn:** Kiểm tra độ sâu khi gọi hàm đệ quy.
* **Test 5 - Trùng lặp hoàn toàn:** Ép thuật toán phải quét đến tận ký tự cuối cùng của chuỗi, qua đó test thử cơ chế fallback sang Insertion Sort có hoạt động đúng lúc không.

#### C. Nhóm chuỗi ưu tiên độ dài - strlenlexi: Quy mô N = 10.000
* **Test 1 - Độ dài hỗn hợp:** Đánh giá độ chính xác của hàm Bucket Sort.
* **Test 2 - Phân phối lệch:** 99% chuỗi ngắn (12 ký tự) và 1% chuỗi cực dài (98 ký tự). Test này kiểm tra khả năng co giãn bộ nhớ của vector bên trong từng xô.
* **Test 3 - Trùng tiền tố, cùng độ dài:** Giống nhau 78 ký tự đầu. Việc phải chuyển mạch liên tục sang bộ so sánh từ điển sẽ gây áp lực rất lớn lên Branch Predictor của CPU.
* **Test 4 - Chiều dài xen kẽ:** Cố ý xếp chuỗi dài ngắn đan xen để làm trật bộ nhớ đệm (phá vỡ tính cục bộ của dữ liệu).
* **Test 5 - Bản sao giống hệt:** Các chuỗi y hệt nhau ở độ dài tối đa, test chi phí truy xuất dữ liệu thông qua chỉ số.

### 4. Kết quả benchmark
Đo đạc thời gian chạy thực tế giữa lần nộp 1 và 2 đã tối ưu hóa:

| Bài toán | Benchmark 1 | Benchmark 2 | Độ cải thiện |
| :--- | :--- | :--- | :--- |
| int | 78 ms | 62 ms | ~20.5% |
| strlexi | 890 ms | 62 ms | ~93.0% |
| strlenlexi | 515 ms | 109 ms | ~78.8% |
