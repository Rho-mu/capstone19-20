import Vue from 'vue'
import Router from 'vue-router'
import Landing from '@/components/Landing'
import Survey from '@/components/Survey'
import UnityPlayer from '@/components/UnityPlayer'
import Identification from '@/components/Identification'
import Warning from '@/components/Warning'
import Login from '@/components/Login'
import Upload from '@/components/Upload'
import Admin from '@/components/Admin'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Landing',
      component: Landing
    },
    {
      path: '/Identification',
      name: 'identification',
      component: Identification
    },
    {
      path: '/login',
      name: 'Login',
      component: Login
    },
    {
      path: '/survey',
      name: 'Survey',
      component: Survey
    },
    {
      path: '/warning',
      name: 'Warning',
      component: Warning
    },
    {
      path: '/upload',
      name: 'Upload',
      component: Upload
    },
    {
      path: '/admin',
      name: 'Admin',
      component: Admin
    },
    {
      path: '/unityplayer',
      name: 'UnityPlayer',
      component: UnityPlayer
    }
  ]
})
