import Vue from 'vue'
import firebase from 'firebase'
import App from './App.vue'
import router from './router'

Vue.config.productionTip = false

let app = firebase.initializeApp
({
  apiKey: "AIzaSyBZM8yAxoZeqEIq30tEcSs4Fh86dbl6L4s",
  authDomain: "acgca-2396d.firebaseapp.com",
  databaseURL: "https://acgca-2396d.firebaseio.com",
  projectId: "acgca-2396d",
  storageBucket: "acgca-2396d.appspot.com",
  messagingSenderId: "796968935884",
  appId: "1:796968935884:web:b903014782ff691c9b3d69",
  measurementId: "G-H8XL1K7K93"
});

export const db = app.database();
export const userRef = db.ref('users');

firebase.auth().onAuthStateChanged(() => {
  if (!app) {
    app = new Vue({
      router,
      render: h => h(App)
    }).$mount('#app');
  }
});
app = new Vue({
  router,
  render: h => h(App)
}).$mount('#app');
