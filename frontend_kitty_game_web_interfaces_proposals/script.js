
  // Initialize Firebase
  var config = {
    apiKey: "AIzaSyC-otDXAsIqq-wt01lzPmww3KsaPdjcDyg",
    authDomain: "cryptokitties-joystick.firebaseapp.com",
    databaseURL: "https://cryptokitties-joystick.firebaseio.com",
    projectId: "cryptokitties-joystick",
    storageBucket: "cryptokitties-joystick.appspot.com",
    messagingSenderId: "1055338785883"
  };
  firebase.initializeApp(config);


const txt = document.getElementById("txt");
const send = document.getElementById("btn");
const list = document.getElementById("list");
const todos = firebase.database().ref("todos");

/*
** 添加 todos
*/
send.addEventListener("click", () => {
	todos.push({
		content: txt.value
	});
	txt.value = "";
});





/*
** 雙向綁定，動態更新
*/
todos.on("value", snapshot => {
	let str = "";
	// let data = snapshot.val();
	let data = [];
	snapshot.forEach(item => {
		data.push({ key: item.key, content: item.val().content });
	});
	
	// 讓新加入的 todo 排到最上面
	data.reverse();
	
	// for (let item in data) {
	// 	str += `<li data-key="${item}">${data[item].content}</li>`;
	// }
	
	for (let i = 0; i < data.length; i++) {
		str += `<li data-key="${data[i].key}">${data[i].content}</li>`;
	}
	list.innerHTML = str;
});





/*
** 移除 todos
*/
list.addEventListener("click", evt => {
	if (evt.target.nodeName === "LI") {
		let key = evt.target.dataset.key;
		todos.child(key).remove();
	}
});
