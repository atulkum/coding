#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
threadsafe_queue::threadsafe_queue(){
}
template<typename T>
threadsafe_queue::threadsafe_queue(const threadsafe_queue& other){
	std::lock_guard<std::mutex> lk(other.mut);
	data_queue = other.data_queue;
}
	
template<typename T>
void threadsafe_queue::push(T new_value){
	std::lock_guard<std::mutex> lk(mut);
	data_queue.push(new_value);
	data_cond.notify_one();
}
template<typename T>
bool threadsafe_queue::try_pop(T& value){
	std::lock_guard<std::mutex> lk(mut);
	if(data_queue.empty()){
		return false;
	}
	value=data_queue.front();
        data_queue.pop();
        return true;
}
template<typename T>
std::shared_ptr<T> threadsafe_queue::try_pop(){
	std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()){
                return std::shared_ptr<T>();
        }
        std::shared_ptr<T> ret(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return ret;
}
       	
template<typename T>
void threadsafe_queue::wait_and_pop(T& value){
	std::unique_lock<std::mutex> lk(mut);
	data_cond.wait(lk, [this](){return !data_queue.empty()});
	value=data_queue.front();
        data_queue.pop();
}
template<typename T>
std::shared_ptr<T> threadsafe_queue::wait_and_pop(){
	std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this](){return !data_queue.empty()});
	std::shared_ptr<T> ret(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return ret;
}
    	
template<typename T>
bool threadsafe_queue::empty() const{
	std::lock_guard<std::mutex> lk(mut);
	return data_queue.empty();
}

