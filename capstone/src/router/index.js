
import firebase from 'firebase'
import Vue from 'vue'
import VueRouter from 'vue-router'
import Login from '../views/Login.vue'
import SignUp from '../views/SignUp.vue'
import Survey from '../views/Survey.vue'
import Landing from '../views/Landing.vue'
import Acgca from '../views/acgca.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/survey',
    name: 'Survey',
    component: Survey,
    meta: {
      requiresAuth: false
    }
  },
  {
    path:  '/login',
    name: 'Login',
    component: Login
  },
  {
    path:  '/sign-up',
    name: 'SignUp',
    component: SignUp
  },
  {
    path: '*', // this redirects anything that doesn't correspond to the login page
    redirect: '/landing'
  },
  {
    path: '/landing', // this redirects anything that doesn't correspond to the login page
    name: 'Landing',
    component: Landing
  },
  {
    path: '/acgca',
    name: 'Acgca',
    component: Acgca, // this will require Auth
    meta: {
      requiresAuth: false
    }
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

router.beforeEach((to, from, next) => {
  const currentUser = firebase.auth().currentUser;
  const requiresAuth = to.matched.some(record => record.meta.requiresAuth);

  if (requiresAuth && !currentUser) next('login');
  // else if (!requiresAuth && currentUser) next('landing');
  else next();
});

export default router;
